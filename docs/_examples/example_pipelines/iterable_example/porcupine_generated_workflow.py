#This is a Nipype generator. Warning, here be dragons.
import sys
import nipype
import nipype.pipeline as pe
import nipype.interfaces.utility as utility
import nipype.interfaces.io as io
import nipype.interfaces.fsl as fsl

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Basic interface class generates identity mappings
NodeHash_862be80 = pe.Node(utility.IdentityInterface(fields=['sub_id']), name = 'NodeName_862be80')
NodeHash_862be80.iterables = [('sub_id', ['sub-01', 'sub-02'])]

#Generic datagrabber module that wraps around glob in an
NodeHash_2aa1150 = pe.Node(io.S3DataGrabber(infields=['sub_id'], outfields=['anat']), name = 'NodeName_2aa1150')
NodeHash_2aa1150.inputs.bucket = 'openneuro'
NodeHash_2aa1150.inputs.sort_filelist = True
NodeHash_2aa1150.inputs.template = '%s/anat/%s_T1w.nii.gz'
NodeHash_2aa1150.inputs.anon = True
NodeHash_2aa1150.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_2aa1150.inputs.local_directory = '/tmp'
NodeHash_2aa1150.inputs.template_args = dict(anat=[['sub_id', 'sub_id']])

#Wraps command **bet**
NodeHash_5df9570 = pe.Node(interface = fsl.BET(), name = 'NodeName_5df9570')

#Generic datasink module to store structured outputs
NodeHash_2de0420 = pe.Node(interface = io.DataSink(), name = 'NodeName_2de0420')
NodeHash_2de0420.inputs.base_directory = '/tmp'

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_862be80, 'sub_id', NodeHash_2de0420, 'container')
analysisflow.connect(NodeHash_5df9570, 'out_file', NodeHash_2de0420, 'BET_results')
analysisflow.connect(NodeHash_2aa1150, 'anat', NodeHash_5df9570, 'in_file')
analysisflow.connect(NodeHash_862be80, 'sub_id', NodeHash_2aa1150, 'sub_id')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 1} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
