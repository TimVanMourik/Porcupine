#This is a NiPype generator. Warning, here be dragons.
import nipype
import nipype.pipeline as pe
import nipype.interfaces.utility as utility
import nipype.interfaces.fsl as fsl
import nipype.interfaces.io as io

WorkingDirectory = "~/Porcupipelines/ThisStudy"
in_file = "/home/lukas/Porcupine/example_workflows/example_data/sub-01/anat/sub-01_T1w.nii.gz"
out_dir = "/home/lukas/Porcupine/example_workflows/iterable_example/out"

#Basic interface class generates identity mappings
NodeHash_1e0b7d0 = pe.Node(utility.IdentityInterface(fields=['frac']), name = 'NodeName_1e0b7d0')
NodeHash_1e0b7d0.iterables = [('frac', [0.2, 0.5])]

#Wraps command **bet**
NodeHash_13f5100 = pe.Node(interface = fsl.BET(), name = 'NodeName_13f5100')
NodeHash_13f5100.inputs.in_file = in_file

#Generic datasink module to store structured outputs
NodeHash_21eb450 = pe.Node(interface = io.DataSink(), name = 'NodeName_21eb450')
NodeHash_21eb450.inputs.base_directory = out_dir
NodeHash_21eb450.inputs.substitutions = [('_frac', 'frac')]

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_1e0b7d0, 'frac', NodeHash_13f5100, 'frac')
analysisflow.connect(NodeHash_13f5100, 'out_file', NodeHash_21eb450, 'betted_file')

#Run the workflow
analysisflow.run()
