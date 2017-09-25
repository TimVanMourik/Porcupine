#!/usr/bin/env python3
import sys
import os
import argparse
import nipype
import nipype.pipeline as pe
import nipype.interfaces.io as io
import nipype.interfaces.fsl as fsl
from glob import glob

def run(command, env={}):
    merged_env = os.environ
    merged_env.update(env)
    process = subprocess.Popen(command, stdout=subprocess.PIPE,
                               stderr=subprocess.STDOUT, shell=True,
                               env=merged_env)
    while True:
        line = process.stdout.readline()
        line = str(line, 'utf-8')[:-1]
        print(line)
        if line == '' and process.poll() != None:
            break
    if process.returncode != 0:
        raise Exception("Non zero return code: %d"%process.returncode)

parser = argparse.ArgumentParser(description='Example BIDS App entrypoint script.')
parser.add_argument('bids_dir', help='The directory with the input dataset '
                    'formatted according to the BIDS standard.')
parser.add_argument('output_dir', help='The directory where the output files '
                    'should be stored. If you are running group level analysis '
                    'this folder should be prepopulated with the results of the'
                    'participant level analysis.')
parser.add_argument('--participant_label', help='The label(s) of the participant(s) that should be analyzed. The label '
                   'corresponds to sub-<participant_label> from the BIDS spec '
                   '(so it does not include "sub-"). If this parameter is not '
                   'provided all subjects should be analyzed. Multiple '
                   'participants can be specified with a space separated list.',
                   nargs="+")

args = parser.parse_args()

subjects_to_analyze = []
# only for a subset of subjects
if args.participant_label:
    subjects_to_analyze = args.participant_label
# for all subjects
else:
    subject_dirs = sorted(glob(os.path.join(args.bids_dir, "sub-*")))
    subjects_to_analyze = [subject_dir.split("-")[-1] for subject_dir in subject_dirs]

bids_dir = args.bids_dir
out_dir = args.output_dir
sub_ids = subjects_to_analyze

#Flexibly collect data from disk to feed into workflows.
NodeHash_230d6a0 = pe.Node(io.SelectFiles(templates={'anat':'sub-{sub_id}/anat/sub-{sub_id}_T1w.nii.gz'}), name = 'NodeName_230d6a0')
NodeHash_230d6a0.inputs.base_directory = bids_dir
NodeHash_230d6a0.iterables = [('sub_id', sub_ids)]

#Wraps command **bet**
NodeHash_24dfec0 = pe.Node(interface = fsl.BET(), name = 'NodeName_24dfec0')

#Generic datasink module to store structured outputs
NodeHash_32ba670 = pe.Node(interface = io.DataSink(), name = 'NodeName_32ba670')
NodeHash_32ba670.inputs.base_directory = out_dir
NodeHash_32ba670.inputs.parameterization = False

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_230d6a0, 'anat', NodeHash_24dfec0, 'in_file')
analysisflow.connect(NodeHash_24dfec0, 'out_file', NodeHash_32ba670, 'BET_results')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 1} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
