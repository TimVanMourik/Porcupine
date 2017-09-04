#This is a Nipype generator. Warning, here be dragons.
import sys
import nipype
import nipype.pipeline as pe
import nipype.interfaces.io as io
import nipype.interfaces.ants as ants
import nipype.interfaces.afni as afni
import nipype.interfaces.fsl as fsl

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Generic datagrabber module that wraps around glob in an
NodeHash_30bb950 = pe.Node(io.S3DataGrabber(outfields=['outfiles']), name = 'NodeName_30bb950')
NodeHash_30bb950.inputs.anon = True
NodeHash_30bb950.inputs.bucket = 'openneuro'
NodeHash_30bb950.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_30bb950.inputs.local_directory = '/tmp'
NodeHash_30bb950.inputs.sort_filelist = True
NodeHash_30bb950.inputs.template = 'sub-01/anat/sub-01_T1w.nii.gz'

#Wraps command **N4BiasFieldCorrection**
NodeHash_1ea4b50 = pe.Node(interface = ants.N4BiasFieldCorrection(), name = 'NodeName_1ea4b50')
NodeHash_1ea4b50.inputs.copy_header = False
NodeHash_1ea4b50.inputs.dimension = 3
NodeHash_1ea4b50.inputs.num_threads = 4
NodeHash_1ea4b50.inputs.save_bias = True

#Wraps command **3dUnifize**
NodeHash_291d6d0 = pe.Node(interface = afni.Unifize(), name = 'NodeName_291d6d0')
NodeHash_291d6d0.inputs.outputtype = 'NIFTI_GZ'

#Wraps command **3dSkullStrip**
NodeHash_1ddfa30 = pe.Node(interface = afni.SkullStrip(), name = 'NodeName_1ddfa30')
NodeHash_1ddfa30.inputs.outputtype = 'NIFTI_GZ'

#Wraps command **3dcalc**
NodeHash_3bd6370 = pe.Node(interface = afni.Calc(), name = 'NodeName_3bd6370')
NodeHash_3bd6370.inputs.expr = 'a*step(b)'
NodeHash_3bd6370.inputs.outputtype = 'NIFTI_GZ'

#Wraps command **fslmaths**
NodeHash_49ddb10 = pe.Node(interface = fsl.Threshold(), name = 'NodeName_49ddb10')
NodeHash_49ddb10.inputs.args = '-bin'
NodeHash_49ddb10.inputs.thresh = 1.e-3

#Wraps command **3dUnifize**
NodeHash_229c200 = pe.Node(interface = afni.Unifize(), name = 'NodeName_229c200')
NodeHash_229c200.inputs.gm = True
NodeHash_229c200.inputs.outputtype = 'NIFTI_GZ'

#Generic datasink module to store structured outputs
NodeHash_3207070 = pe.Node(interface = io.DataSink(), name = 'NodeName_3207070')
NodeHash_3207070.inputs.base_directory = '/tmp'

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_30bb950, 'outfiles', NodeHash_1ea4b50, 'input_image')
analysisflow.connect(NodeHash_1ea4b50, 'output_image', NodeHash_291d6d0, 'in_file')
analysisflow.connect(NodeHash_291d6d0, 'out_file', NodeHash_1ddfa30, 'in_file')
analysisflow.connect(NodeHash_1ea4b50, 'bias_image', NodeHash_3207070, 'bias_image')
analysisflow.connect(NodeHash_291d6d0, 'out_file', NodeHash_3bd6370, 'in_file_a')
analysisflow.connect(NodeHash_1ddfa30, 'out_file', NodeHash_3bd6370, 'in_file_b')
analysisflow.connect(NodeHash_3bd6370, 'out_file', NodeHash_49ddb10, 'in_file')
analysisflow.connect(NodeHash_3bd6370, 'out_file', NodeHash_229c200, 'in_file')
analysisflow.connect(NodeHash_49ddb10, 'out_file', NodeHash_3207070, 'out_mask')
analysisflow.connect(NodeHash_229c200, 'out_file', NodeHash_3207070, 'out_file')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 1} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
