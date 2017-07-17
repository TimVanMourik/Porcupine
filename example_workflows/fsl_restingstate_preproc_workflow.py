""" Example (FSL) resting-state preprocessing workflow that can be implemented in Porcupine.
Based on the implementation/description from:
http://nipype.readthedocs.io/en/latest/interfaces/generated/workflows.rsfmri/fsl.resting.html
"""

import os
import os.path as op
import nipype.pipeline as pe
import nipype.interfaces.utility as util
from nipype.interfaces import fsl
from nipype.algorithms import confounds
from glob import glob
from code import (t1_paths, raw_data_path, raw_func_paths, mcf_func_paths,
                  meanbold_paths, derivatives_path, cdir)


def create_fsl_restingstate_preproc_workflow(name='fsl_restingstate_preproc'):
    """ FSL resting-state preprocessing workflow. """

    restpreproc = pe.Workflow(name=name)

    # Define nodes
    inputnode = pe.Node(interface=util.IdentityInterface(fields=['func',
                                                                 'num_noise_components',
                                                                 'highpass_sigma',
                                                                 'lowpass_sigma',
                                                                 'TR'
                                                                 ]),
                        name='inputspec')
    outputnode = pe.Node(interface=util.IdentityInterface(fields=[
        'noise_mask_file',
        'filtered_file',
    ]),
        name='outputspec')

    slicetimer = pe.Node(fsl.SliceTimer(), name='slicetimer')

    realigner = pe.Node(fsl.MCFLIRT(save_mats=True, stats_imgs=True),
                        name='realigner')
    splitter = pe.Node(fsl.Split(dimension='t'), name='splitter')
    warper = pe.MapNode(fsl.ApplyWarp(interp='spline'),
                        iterfield=['in_file', 'premat'],
                        name='warper')
    joiner = pe.Node(fsl.Merge(dimension='t'), name='joiner')
    tsnr = pe.Node(confounds.TSNR(regress_poly=2), name='tsnr')
    getthresh = pe.Node(interface=fsl.ImageStats(op_string='-p 98'),
                        name='getthreshold')
    threshold_stddev = pe.Node(fsl.Threshold(), name='threshold')
    compcor = pe.Node(confounds.ACompCor(components_file="noise_components.txt",
                                         use_regress_poly=False,
                                         header_prefix=''),
                      name='compcor')
    remove_noise = pe.Node(fsl.FilterRegressor(filter_all=True),
                           name='remove_noise')
    bandpass_filter = pe.Node(fsl.TemporalFilter(),
                              name='bandpass_filter')

    # Define connections
    restpreproc.connect(inputnode, 'func', slicetimer, 'in_file')
    restpreproc.connect(inputnode, 'TR', slicetimer, 'time_repetition')
    restpreproc.connect(slicetimer, 'slice_time_corrected_file',
                        realigner, 'in_file')
    restpreproc.connect(realigner, 'out_file', splitter, 'in_file')
    restpreproc.connect(realigner, 'mat_file', warper, 'premat')
    restpreproc.connect(realigner, 'variance_img', warper, 'ref_file')
    restpreproc.connect(splitter, 'out_files', warper, 'in_file')
    restpreproc.connect(warper, 'out_file', joiner, 'in_files')
    restpreproc.connect(joiner, 'merged_file', tsnr, 'in_file')
    restpreproc.connect(tsnr, 'stddev_file', threshold_stddev, 'in_file')
    restpreproc.connect(tsnr, 'stddev_file', getthresh, 'in_file')
    restpreproc.connect(getthresh, 'out_stat', threshold_stddev, 'thresh')
    restpreproc.connect(realigner, 'out_file',
                        compcor, 'realigned_file')
    restpreproc.connect(threshold_stddev, 'out_file',
                        compcor, 'mask_files')
    restpreproc.connect(inputnode, 'num_noise_components',
                        compcor, 'num_components')
    restpreproc.connect(tsnr, 'detrended_file',
                        remove_noise, 'in_file')
    restpreproc.connect(compcor, 'components_file',
                        remove_noise, 'design_file')
    restpreproc.connect(inputnode, 'highpass_sigma',
                        bandpass_filter, 'highpass_sigma')
    restpreproc.connect(inputnode, 'lowpass_sigma',
                        bandpass_filter, 'lowpass_sigma')
    restpreproc.connect(remove_noise, 'out_file', bandpass_filter, 'in_file')
    restpreproc.connect(threshold_stddev, 'out_file',
                        outputnode, 'noise_mask_file')
    restpreproc.connect(bandpass_filter, 'out_file',
                        outputnode, 'filtered_file')

    return restpreproc


if __name__ == '__main__':

    rs_wf = create_fsl_restingstate_preproc_workflow()
    rs_wf.inputs.inputspec.func = mcf_func_paths[0]
    rs_wf.inputs.inputspec.num_noise_components = 6
    rs_wf.inputs.inputspec.highpass_sigma = 25
    rs_wf.inputs.inputspec.lowpass_sigma = 3
    rs_wf.inputs.inputspec.TR = 2.0
    rs_wf.base_dir = '../data/workflows_workingdirs'
    rs_wf.write_graph(dotfilename=op.join(cdir, 'fsl_restingstate_preproc_workflow_graph'))
    rs_wf.run()