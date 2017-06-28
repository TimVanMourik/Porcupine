""" Example (AFNI) skullstrip workflow that can be implemented in Porcupine.
Based on the implementation/description from the niworkflows package:
https://github.com/poldracklab/niworkflows/blob/master/niworkflows/anat/skullstrip.py.
"""

import os
import os.path as op
import nipype.pipeline as pe
import nipype.interfaces.utility as util
from nipype.interfaces import afni, ants, fsl


def create_afni_skullstripping_workflow(name='afni_skullstrip', unifize=False, n4_nthreads=1):

    workflow = pe.Workflow(name=name)
    inputnode = pe.Node(util.IdentityInterface(fields=['in_file']),
                        name='inputspec')
    outputnode = pe.Node(util.IdentityInterface(
        fields=['bias_corrected', 'out_file', 'out_mask', 'bias_image']),
        name='outputspec')

    inu_n4 = pe.Node(
        ants.N4BiasFieldCorrection(dimension=3, save_bias=True,
                                   num_threads=n4_nthreads,
                                   ),
        n_procs=n4_nthreads,
        name='inu_n4')

    sstrip = pe.Node(afni.SkullStrip(outputtype='NIFTI_GZ'), name='skullstrip')
    sstrip_orig_vol = pe.Node(afni.Calc(
        expr='a*step(b)', outputtype='NIFTI_GZ'), name='sstrip_orig_vol')
    binarize = pe.Node(fsl.Threshold(args='-bin', thresh=1.e-3),
                       name='binarize')

    if unifize:
        # Add two unifize steps, pre- and post- skullstripping.
        inu_uni_0 = pe.Node(afni.Unifize(outputtype='NIFTI_GZ'),
                            name='unifize_pre_skullstrip')
        inu_uni_1 = pe.Node(afni.Unifize(gm=True, outputtype='NIFTI_GZ'),
                            name='unifize_post_skullstrip')
        workflow.connect([
            (inu_n4, inu_uni_0, [('output_image', 'in_file')]),
            (inu_uni_0, sstrip, [('out_file', 'in_file')]),
            (inu_uni_0, sstrip_orig_vol, [('out_file', 'in_file_a')]),
            (sstrip_orig_vol, inu_uni_1, [('out_file', 'in_file')]),
            (inu_uni_1, outputnode, [('out_file', 'out_file')]),
            (inu_uni_0, outputnode, [('out_file', 'bias_corrected')]),
        ])
    else:
        workflow.connect([
            (inputnode, sstrip_orig_vol, [('in_file', 'in_file_a')]),
            (inu_n4, sstrip, [('output_image', 'in_file')]),
            (sstrip_orig_vol, outputnode, [('out_file', 'out_file')]),
            (inu_n4, outputnode, [('output_image', 'bias_corrected')]),
        ])

    # Remaining connections
    workflow.connect([
        (sstrip, sstrip_orig_vol, [('out_file', 'in_file_b')]),
        (inputnode, inu_n4, [('in_file', 'input_image')]),
        (sstrip_orig_vol, binarize, [('out_file', 'in_file')]),
        (binarize, outputnode, [('out_file', 'out_mask')]),
        (inu_n4, outputnode, [('bias_image', 'bias_image')]),
    ])

    return workflow

if __name__ == '__main__':

    import subprocess
    root_dir = op.dirname(op.dirname(op.abspath(__file__)))
    data_dir = op.join(root_dir, 'example_data')
    if not op.isdir(data_dir):
        script_loc = op.join(root_dir, 'utilities', 'download_openfmri_data.py')
        subprocess.call('python %s -d ds000101 -o %s' % (script_loc, data_dir),
                        shell=True)

    ss_wf = create_afni_skullstripping_workflow()
    ss_wf.inputs.inputspec.in_file = op.join(data_dir,
                                             'sub-01/anat/sub-01_T1w.nii.gz')
    ss_wf.run()
