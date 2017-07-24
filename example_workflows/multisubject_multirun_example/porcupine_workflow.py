#This is a NiPype generator. Warning, here be dragons.
import nipype
import nipype.pipeline as pe
import nipype.interfaces.utility as utility
import nipype.interfaces.io as io
import nipype.interfaces.fsl as fsl

WorkingDirectory = "~/Porcupipelines/ThisStudy"
base_dir = "/home/lukas/Porcupine/example_workflows/example_data"
out_dir = "/home/lukas/Porcupine/example_workflows/multisubject_multirun_example/out"

#Basic interface class generates identity mappings
NodeHash_2025520 = pe.Node(utility.IdentityInterface(fields=['sub_id']), name = 'NodeName_2025520')
NodeHash_2025520.iterables = [('sub_id', ['sub-01', 'sub-02'])]

#Flexibly collect data from disk to feed into workflows.
NodeHash_220d510 = pe.Node(io.SelectFiles(templates={'func':'{sub_id}/func/sub-01_task-simon_run-*_bold.nii.gz'}), name = 'NodeName_220d510')
NodeHash_220d510.inputs.base_directory = base_dir
NodeHash_220d510.inputs.sort_filelist = True

#Wraps command **mcflirt**
NodeHash_3422140 = pe.MapNode(interface = fsl.MCFLIRT(), name = 'NodeName_3422140', iterfield = ['in_file'])
NodeHash_3422140.inputs.save_mats = True
NodeHash_3422140.inputs.save_plots = True
NodeHash_3422140.inputs.save_rms = True

#Generic datasink module to store structured outputs
NodeHash_2f6e6f0 = pe.Node(interface = io.DataSink(), name = 'NodeName_2f6e6f0')
NodeHash_2f6e6f0.inputs.base_directory = out_dir
NodeHash_2f6e6f0.inputs.parameterization = False

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_3422140, 'par_file', NodeHash_2f6e6f0, 'moco.motion_params')
analysisflow.connect(NodeHash_3422140, 'out_file', NodeHash_2f6e6f0, 'moco')
analysisflow.connect(NodeHash_2025520, 'sub_id', NodeHash_2f6e6f0, 'container')
analysisflow.connect(NodeHash_220d510, 'func', NodeHash_3422140, 'in_file')
analysisflow.connect(NodeHash_2025520, 'sub_id', NodeHash_220d510, 'sub_id')

#Run the workflow
analysisflow.run()
