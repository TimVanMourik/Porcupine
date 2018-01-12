#This is a Nipype generator. Warning, here be dragons.
import sys
import nipype
import nipype.pipeline as pe
import nipype.interfaces.utility as utility
import nipype.interfaces.io as io
import nipype.interfaces.fsl as fsl

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Basic interface class generates identity mappings
NodeHash_1c35840 = pe.Node(utility.IdentityInterface(fields=['sub_id']), name = 'NodeName_1c35840')
NodeHash_1c35840.iterables = [('sub_id', ['sub-01', 'sub-02'])]

#Generic datagrabber module that wraps around glob in an
NodeHash_1d9b790 = pe.Node(io.S3DataGrabber(infields=['sub_id'], outfields=['anat']), name = 'NodeName_1d9b790')
NodeHash_1d9b790.inputs.bucket = 'openneuro'
NodeHash_1d9b790.inputs.sort_filelist = True
NodeHash_1d9b790.inputs.template = '%s/anat/%s_T1w.nii.gz'
NodeHash_1d9b790.inputs.anon = True
NodeHash_1d9b790.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_1d9b790.inputs.local_directory = '/tmp'
NodeHash_1d9b790.inputs.template_args = dict(anat=[['sub_id', 'sub_id']])

#Wraps command **bet**
NodeHash_28c60a0 = pe.Node(interface = fsl.BET(), name = 'NodeName_28c60a0')

#Generic datasink module to store structured outputs
NodeHash_308ebc0 = pe.Node(interface = io.DataSink(), name = 'NodeName_308ebc0')

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_1c35840, 'sub_id', NodeHash_1d9b790, 'sub_id')
analysisflow.connect(NodeHash_1d9b790, 'anat', NodeHash_28c60a0, 'in_file')
analysisflow.connect(NodeHash_1c35840, 'sub_id', NodeHash_308ebc0, 'container')
analysisflow.connect(NodeHash_28c60a0, 'out_file', NodeHash_308ebc0, 'BET_results')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 1} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
