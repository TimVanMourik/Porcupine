""" In these modules, several workflows for (f)MRI preprocessing are implemented
using the Nipype package. Each function in these modules defines a specific
workflow, which is returned (i.e. a Nipype "Workflow" object) upon calling the
function.

Lukas Snoek, 31 May 2017
"""

import os.path as op
from glob import glob

# Some 'global' (scope=this dir) variables
cdir = op.dirname(__file__)
raw_data_path = op.join(op.dirname(cdir), 'data', 'bids_converted')
derivatives_path = op.join(op.dirname(cdir), 'data', 'derivatives')

raw_func_paths = sorted(glob(op.join(raw_data_path, '*', 'func',
                                     '*_task-rest_bold.nii.gz')))

mcf_func_paths = sorted(glob(op.join(derivatives_path, '*', '*_mcf.nii.gz')))
meanbold_paths = sorted(glob(op.join(derivatives_path, '*', '*_mean.nii.gz')))
t1_paths = sorted(glob(op.join(raw_data_path, '*', 'anat', '*_T1w.nii.gz')))
