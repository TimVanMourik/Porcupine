#This is a NiPype generator. Warning, here be dragons.
import nipype
import nipype.pipeline as pe
import nipype.interfaces.fsl as fsl
import nipype.interfaces.io as io

WorkingDirectory = "~/Porcupipelines/ThisStudy"
in_file = "/home/lukas/Porcupine/example_workflows/example_data/sub-01/anat/sub-01_T1w.nii.gz"
out_dir = "/home/lukas/Porcupine/example_workflows/simple_example/out"

#Wraps command **bet**
NodeHash_19c4a70 = pe.Node(interface = fsl.BET(), name = 'NodeName_19c4a70')
NodeHash_19c4a70.inputs.in_file = in_file

#Generic datasink module to store structured outputs
NodeHash_1c9dee0 = pe.Node(interface = io.DataSink(), name = 'NodeName_1c9dee0')
NodeHash_1c9dee0.inputs.base_directory = out_dir

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_19c4a70, 'out_file', NodeHash_1c9dee0, 'betted_file')

#Run the workflow
analysisflow.run()

