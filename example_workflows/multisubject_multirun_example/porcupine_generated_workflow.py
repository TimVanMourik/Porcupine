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
NodeHash_7f52d40 = pe.Node(utility.IdentityInterface(fields=['sub_id']), name = 'NodeName_7f52d40')
NodeHash_7f52d40.iterables = [('sub_id', ['sub-01', 'sub-02'])]

#Generic datagrabber module that wraps around glob in an
NodeHash_b56d8c0 = pe.Node(interface = io.S3DataGrabber(), name = 'NodeName_b56d8c0')
NodeHash_b56d8c0.inputs.anon = True
NodeHash_b56d8c0.inputs.bucket = 'openneuro'
NodeHash_b56d8c0.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_b56d8c0.inputs.local_directory = '/tmp'
NodeHash_b56d8c0.inputs.sort_filelist = True
NodeHash_b56d8c0.inputs.template = '%s/func/%s_task-simon_run-%i_bold.nii.gz'
NodeHash_b56d8c0.inputs.template_args = dict(func=[['sub_id', 'sub_id', 'run_id']])
NodeHash_b56d8c0.inputs.run_id = [1, 2]

#Wraps command **mcflirt**
NodeHash_7c488b0 = pe.MapNode(interface = fsl.MCFLIRT(), name = 'NodeName_7c488b0', iterfield = ['in_file'])
NodeHash_7c488b0.inputs.save_mats = True
NodeHash_7c488b0.inputs.save_plots = True
NodeHash_7c488b0.inputs.save_rms = True

#Generic datasink module to store structured outputs
NodeHash_afbbb00 = pe.Node(interface = io.DataSink(), name = 'NodeName_afbbb00')
NodeHash_afbbb00.inputs.base_directory = out_dir
NodeHash_afbbb00.inputs.parameterization = False

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_7c488b0, 'out_file', NodeHash_afbbb00, 'moco')
analysisflow.connect(NodeHash_7c488b0, 'par_file', NodeHash_afbbb00, 'moco.motion_params')
analysisflow.connect(NodeHash_b56d8c0, 'func', NodeHash_7c488b0, 'in_file')
analysisflow.connect(NodeHash_7f52d40, 'sub_id', NodeHash_b56d8c0, 'sub_id')
analysisflow.connect(NodeHash_7f52d40, 'sub_id', NodeHash_afbbb00, 'container')

#Run the workflow
analysisflow.run()
