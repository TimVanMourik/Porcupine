#This is a Nipype generator. Warning, here be dragons.
import sys
import nipype
import nipype.pipeline as pe
import nipype.interfaces.io as io
import nipype.interfaces.fsl as fsl

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Generic datagrabber module that wraps around glob in an
NodeHash_2901d30 = pe.Node(io.S3DataGrabber(outfields=['outfiles']), name = 'NodeName_2901d30')
NodeHash_2901d30.inputs.bucket = 'openneuro'
NodeHash_2901d30.inputs.sort_filelist = True
NodeHash_2901d30.inputs.template = 'sub-01/anat/sub-01_T1w.nii.gz'
NodeHash_2901d30.inputs.anon = True
NodeHash_2901d30.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_2901d30.inputs.local_directory = '/tmp'

#Wraps command **bet**
NodeHash_3924700 = pe.Node(interface = fsl.BET(), name = 'NodeName_3924700')

#Generic datasink module to store structured outputs
NodeHash_6110c20 = pe.Node(interface = io.DataSink(), name = 'NodeName_6110c20')
NodeHash_6110c20.inputs.base_directory = '/tmp'

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_3924700, 'out_file', NodeHash_6110c20, 'BET_results')
analysisflow.connect(NodeHash_2901d30, 'outfiles', NodeHash_3924700, 'in_file')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 1} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
