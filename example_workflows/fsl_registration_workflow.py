""" Example (FSL) registration workflow that can be implemented in Porcupine.
Based on the implementation/description from:
http://nipype.readthedocs.io/en/latest/interfaces/generated/workflows.fmri/fsl.preprocess.html.
"""

import os
import os.path as op
import nipype.pipeline as pe
import nipype.interfaces.utility as util
from nipype.interfaces import fsl


def create_fsl_registration_workflow(name='registration'):
    """ FSL registration workflow. """

    register = pe.Workflow(name=name)

    inputnode = pe.Node(interface=util.IdentityInterface(fields=['source_files',
                                                                 'anatomical_image',
                                                                 'target_image']),
                        name='inputspec')
    outputnode = pe.Node(
        interface=util.IdentityInterface(fields=['func2anat_transform',
                                                 'anat2target_transform',
                                                 'transformed_files',
                                                 'transformed_mean',
                                                 ]),
        name='outputspec')

    stripper = pe.Node(fsl.BET(), name='stripper')
    register.connect(inputnode, 'anatomical_image', stripper, 'in_file')
    fast = pe.Node(fsl.FAST(), name='fast')
    register.connect(stripper, 'out_file', fast, 'in_files')

    """
    Binarize the segmentation
    """

    binarize = pe.Node(fsl.ImageMaths(op_string='-nan -thr 0.5 -bin'),
                       name='binarize')

    #pickindex = lambda x, i: x[i]
    pickindex = pe.Node(interface=util.Select(index=2), name='pickindex')

    register.connect(fast, 'partial_volume_files', pickindex, 'inlist')
    register.connect(pickindex, 'out', binarize, 'in_file')

    """
    Calculate rigid transform from mean image to anatomical image
    """
    pickfirst = pe.Node(interface=util.Select(index=0), name='pickfirst')
    meanbold = pe.Node(interface=fsl.MeanImage(), name='meanbold')

    register.connect(inputnode, 'source_files', pickfirst, 'inlist')
    register.connect(pickfirst, 'out', meanbold, 'in_file')

    mean2anat = pe.Node(fsl.FLIRT(), name='mean2anat')
    mean2anat.inputs.dof = 6
    register.connect(meanbold, 'out_file', mean2anat, 'in_file')
    register.connect(stripper, 'out_file', mean2anat, 'reference')

    """
    Now use bbr cost function to improve the transform
    """

    mean2anatbbr = pe.Node(fsl.FLIRT(), name='mean2anatbbr')
    mean2anatbbr.inputs.dof = 6
    mean2anatbbr.inputs.cost = 'bbr'
    mean2anatbbr.inputs.schedule = op.join(os.getenv('FSLDIR'),
                                                'etc/flirtsch/bbr.sch')
    register.connect(meanbold, 'out_file', mean2anatbbr, 'in_file')
    register.connect(binarize, 'out_file', mean2anatbbr, 'wm_seg')
    register.connect(inputnode, 'anatomical_image', mean2anatbbr, 'reference')
    register.connect(mean2anat, 'out_matrix_file',
                     mean2anatbbr, 'in_matrix_file')

    """
    Calculate affine transform from anatomical to target
    """

    anat2target_affine = pe.Node(fsl.FLIRT(), name='anat2target_linear')
    anat2target_affine.inputs.searchr_x = [-180, 180]
    anat2target_affine.inputs.searchr_y = [-180, 180]
    anat2target_affine.inputs.searchr_z = [-180, 180]
    register.connect(stripper, 'out_file', anat2target_affine, 'in_file')
    register.connect(inputnode, 'target_image',
                     anat2target_affine, 'reference')

    """
    Calculate nonlinear transform from anatomical to target
    """

    # Instead of using a config file (as in the original nipype workflow,
    # we just hard-code the fnirt args)
    anat2target_nonlinear = pe.Node(fsl.FNIRT(in_fwhm=[8, 4, 2, 2],
                                              subsampling_scheme=[4, 2, 1, 1],
                                              warp_resolution =(6, 6, 6),
                                              output_type='NIFTI_GZ'),
                                    name='anat2target_nonlinear')

    anat2target_nonlinear.inputs.fieldcoeff_file = True
    register.connect(anat2target_affine, 'out_matrix_file',
                     anat2target_nonlinear, 'affine_file')
    register.connect(inputnode, 'anatomical_image',
                     anat2target_nonlinear, 'in_file')
    register.connect(inputnode, 'target_image',
                     anat2target_nonlinear, 'ref_file')

    """
    Transform the mean image. First to anatomical and then to target
    """

    warpmean = pe.Node(fsl.ApplyWarp(interp='spline'), name='warpmean')
    register.connect(meanbold, 'out_file', warpmean, 'in_file')
    register.connect(mean2anatbbr, 'out_matrix_file', warpmean, 'premat')
    register.connect(inputnode, 'target_image', warpmean, 'ref_file')
    register.connect(anat2target_nonlinear, 'fieldcoeff_file',
                     warpmean, 'field_file')

    """
    Transform the remaining images. First to anatomical and then to target
    """

    warpall = pe.MapNode(fsl.ApplyWarp(interp='spline'),
                         iterfield=['in_file'],
                         nested=True,
                         name='warpall')
    register.connect(inputnode, 'source_files', warpall, 'in_file')
    register.connect(mean2anatbbr, 'out_matrix_file', warpall, 'premat')
    register.connect(inputnode, 'target_image', warpall, 'ref_file')
    register.connect(anat2target_nonlinear, 'fieldcoeff_file',
                     warpall, 'field_file')

    """
    Assign all the output files
    """

    register.connect(warpmean, 'out_file', outputnode, 'transformed_mean')
    register.connect(warpall, 'out_file', outputnode, 'transformed_files')
    register.connect(mean2anatbbr, 'out_matrix_file',
                     outputnode, 'func2anat_transform')
    register.connect(anat2target_nonlinear, 'fieldcoeff_file',
                     outputnode, 'anat2target_transform')

    return register

if __name__ == '__main__':

    import subprocess
    from glob import glob

    root_dir = op.dirname(op.dirname(op.abspath(__file__)))
    data_dir = op.join(root_dir, 'example_data')
    if not op.isdir(data_dir):
        script_loc = op.join(root_dir, 'utilities', 'download_openfmri_data.py')
        subprocess.call('python %s -d ds000101 -o %s' % (script_loc, data_dir),
                        shell=True)


    reg_wf = create_fsl_registration_workflow()
    reg_wf.inputs.inputspec.target_image = fsl.Info.standard_image('MNI152_T1_2mm_brain.nii.gz')
    reg_wf.inputs.inputspec.source_files = glob(op.join(data_dir, 'sub-01',
                                                        'func', '*.nii.gz'))
    reg_wf.inputs.inputspec.anatomical_image = op.join(data_dir, 'sub-01',
                                                       'anat',
                                                       'sub-01_T1w.nii.gz')
    reg_wf.base_dir = op.join(op.dirname(__file__), 'workingdir')
    graph_fn = op.join(op.dirname(op.abspath(__file__)), 'fsl_registration_workflow_graph')
    reg_wf.write_graph(dotfilename=graph_fn)
    os.remove(graph_fn)
    reg_wf.run()
