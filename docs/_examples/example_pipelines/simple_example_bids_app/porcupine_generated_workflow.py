#This is a Nipype generator. Warning, here be dragons.
import sys
import nipype
import nipype.pipeline as pe
import nipype.interfaces.io as io
import nipype.interfaces.fsl as fsl

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Generic datagrabber module that wraps around glob in an
NodeHash_17c5c70 = pe.Node(io.S3DataGrabber(outfields=['outfiles']), name = 'NodeName_17c5c70')
NodeHash_17c5c70.inputs.bucket = 'openneuro'
NodeHash_17c5c70.inputs.sort_filelist = True
NodeHash_17c5c70.inputs.template = 'sub-01/anat/sub-01_T1w.nii.gz'
NodeHash_17c5c70.inputs.anon = True
NodeHash_17c5c70.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_17c5c70.inputs.local_directory = '/tmp'

#Wraps command **bet**
NodeHash_211a5f0 = pe.Node(interface = fsl.BET(), name = 'NodeName_211a5f0')

#Generic datasink module to store structured outputs
NodeHash_236ab50 = pe.Node(interface = io.DataSink(), name = 'NodeName_236ab50')
NodeHash_236ab50.inputs.base_directory = '/tmp'

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_211a5f0, 'out_file', NodeHash_236ab50, 'BET_results')
analysisflow.connect(NodeHash_17c5c70, 'outfiles', NodeHash_211a5f0, 'in_file')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 1} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
