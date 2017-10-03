#!/usr/bin/env python
import sys
import argparse
import nipype
import nipype.pipeline as pe
import nipype.interfaces.io as io
import nipype.interfaces.fsl as fsl

parser = argparse.ArgumentParser(description='Example skullstripping BIDS App entrypoint script.')
parser.add_argument('bids_dir', help='The directory with the input dataset '
                    'formatted according to the BIDS standard.')
parser.add_argument('output_dir', help='The directory where the output files '
                    'should be stored. If you are running group level analysis '
                    'this folder should be prepopulated with the results of the'
                    'participant level analysis.')
parser.add_argument('analysis_level', help='Level of the analysis that will be performed. '
                    'Multiple participant level analyses can be run independently '
                    '(in parallel) using the same output_dir.',
                    choices=['participant', 'group'])
parser.add_argument('--participant_label', help='The label(s) of the participant(s) '
                   'that should be analyzed. The label '
                   'corresponds to sub-<participant_label> from the BIDS spec '
                   '(so it does not include "sub-"). If this parameter is not '
                   'provided all subjects should be analyzed. Multiple '
                   'participants can be specified with a space separated list.',
                   nargs="+")
parser.add_argument('--frac', default=0.3, type=float, dest='frac',
                    help='Fractional intensity threshold parameter for FSL BET')

args = parser.parse_args()
bids_dir = args.bids_dir
out_dir = args.output_dir
frac = args.frac

# Extract sub_ids for SelectFiles
if args.participant_label:
    sub_ids = args.participant_label
# for all subjects
else:
    subject_dirs = glob(os.path.join(args.bids_dir, "sub-*"))
    sub_ids = [subject_dir.split("-")[-1] for subject_dir in subject_dirs]

#Flexibly collect data from disk to feed into workflows.
NodeHash_1fc3610 = pe.Node(io.SelectFiles(templates={'anat':'sub-{sub_id}/anat/sub-{sub_id}_T1w.nii.gz'}), name = 'NodeName_1fc3610')
NodeHash_1fc3610.inputs.base_directory = bids_dir
NodeHash_1fc3610.iterables = [('sub_id', sub_ids)]

#Wraps command **bet**
NodeHash_22ba310 = pe.Node(interface = fsl.BET(), name = 'NodeName_22ba310')
NodeHash_22ba310.inputs.frac = frac

#Generic datasink module to store structured outputs
NodeHash_317bde0 = pe.Node(interface = io.DataSink(), name = 'NodeName_317bde0')
NodeHash_317bde0.inputs.base_directory = out_dir
NodeHash_317bde0.inputs.parameterization = False

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_1fc3610, 'anat', NodeHash_22ba310, 'in_file')
analysisflow.connect(NodeHash_22ba310, 'out_file', NodeHash_317bde0, 'BET_results')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 1} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
