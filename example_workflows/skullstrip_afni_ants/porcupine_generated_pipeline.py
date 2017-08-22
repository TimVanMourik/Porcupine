#This is a NiPype generator. Warning, here be dragons.
import nipype
import nipype.pipeline as pe
import nipype.interfaces.io as io
import nipype.interfaces.ants as ants
import nipype.interfaces.afni as afni
import nipype.interfaces.fsl as fsl

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Generic datagrabber module that wraps around glob in an
NodeHash_2d63780 = pe.Node(io.S3DataGrabber(), name = 'NodeName_2d63780')
NodeHash_2d63780.inputs.anon = True
NodeHash_2d63780.inputs.bucket = 'openneuro'
NodeHash_2d63780.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_2d63780.inputs.local_directory = '/tmp'
NodeHash_2d63780.inputs.sort_filelist = True
NodeHash_2d63780.inputs.template = 'sub-01/anat/sub-01_T1w.nii.gz'

#Wraps command **N4BiasFieldCorrection**
NodeHash_2cbfbc0 = pe.Node(interface = ants.N4BiasFieldCorrection(), name = 'NodeName_2cbfbc0')
NodeHash_2cbfbc0.inputs.save_bias = True
NodeHash_2cbfbc0.inputs.dimension = 3
NodeHash_2cbfbc0.inputs.num_threads = 4

#Wraps command **3dUnifize**
NodeHash_6ae34f0 = pe.Node(interface = afni.Unifize(), name = 'NodeName_6ae34f0')
NodeHash_6ae34f0.inputs.outputtype = 'NIFTI_GZ'

#Wraps command **3dSkullStrip**
NodeHash_5770380 = pe.Node(interface = afni.SkullStrip(), name = 'NodeName_5770380')
NodeHash_5770380.inputs.outputtype = 'NIFTI_GZ'

#Wraps command **3dcalc**
NodeHash_2c7fe50 = pe.Node(interface = afni.Calc(), name = 'NodeName_2c7fe50')
NodeHash_2c7fe50.inputs.expr = 'a*step(b)'
NodeHash_2c7fe50.inputs.outputtype = 'NIFTI_GZ'

#Wraps command **3dUnifize**
NodeHash_6ad7e30 = pe.Node(interface = afni.Unifize(), name = 'NodeName_6ad7e30')
NodeHash_6ad7e30.inputs.gm = True
NodeHash_6ad7e30.inputs.outputtype = 'NIFTI_GZ'

#Wraps command **fslmaths**
NodeHash_4f71290 = pe.Node(interface = fsl.Threshold(), name = 'NodeName_4f71290')
NodeHash_4f71290.inputs.thresh = 1.e-3
NodeHash_4f71290.inputs.args = '-bin'

#Generic datasink module to store structured outputs
NodeHash_3b95bb0 = pe.Node(interface = io.DataSink(), name = 'NodeName_3b95bb0')

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_2cbfbc0, 'bias_image', NodeHash_3b95bb0, 'bias_image')
analysisflow.connect(NodeHash_6ad7e30, 'out_file', NodeHash_3b95bb0, 'out_file')
analysisflow.connect(NodeHash_4f71290, 'out_file', NodeHash_3b95bb0, 'out_mask')
analysisflow.connect(NodeHash_2c7fe50, 'out_file', NodeHash_4f71290, 'in_file')
analysisflow.connect(NodeHash_5770380, 'out_file', NodeHash_2c7fe50, 'in_file_b')
analysisflow.connect(NodeHash_2c7fe50, 'out_file', NodeHash_6ad7e30, 'in_file')
analysisflow.connect(NodeHash_6ae34f0, 'out_file', NodeHash_2c7fe50, 'in_file_a')
analysisflow.connect(NodeHash_6ae34f0, 'out_file', NodeHash_5770380, 'in_file')
analysisflow.connect(NodeHash_2cbfbc0, 'output_image', NodeHash_6ae34f0, 'in_file')
analysisflow.connect(NodeHash_2d63780, 'outfiles', NodeHash_2cbfbc0, 'input_image')

#Run the workflow
analysisflow.run()
