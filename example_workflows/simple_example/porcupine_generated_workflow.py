#This is a NiPype generator. Warning, here be dragons.
import nipype
import nipype.pipeline as pe
import nipype.interfaces.io as io
import nipype.interfaces.fsl as fsl

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Generic datagrabber module that wraps around glob in an
NodeHash_276f060 = pe.Node(interface = io.S3DataGrabber(), name = 'NodeName_276f060')
NodeHash_276f060.inputs.bucket = 'openneuro'
NodeHash_276f060.inputs.sort_filelist = True
NodeHash_276f060.inputs.template = 'sub-01/anat/sub-01_T1w.nii.gz'
NodeHash_276f060.inputs.anon = True
NodeHash_276f060.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_276f060.inputs.local_directory = '/tmp'

#Wraps command **bet**
NodeHash_2b375f0 = pe.Node(interface = fsl.BET(), name = 'NodeName_2b375f0')

#Generic datasink module to store structured outputs
NodeHash_35efac0 = pe.Node(interface = io.DataSink(), name = 'NodeName_35efac0')
NodeHash_35efac0.inputs.base_directory = '/tmp'

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_2b375f0, 'out_file', NodeHash_35efac0, 'BET_results')
analysisflow.connect(NodeHash_276f060, 'outfiles', NodeHash_2b375f0, 'in_file')

#Run the workflow
analysisflow.run()
