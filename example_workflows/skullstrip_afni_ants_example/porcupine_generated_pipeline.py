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
NodeHash_84e35c0 = pe.Node(io.S3DataGrabber(outfields=['outfiles']), name = 'NodeName_84e35c0')
NodeHash_84e35c0.inputs.bucket = 'openneuro'
NodeHash_84e35c0.inputs.sort_filelist = True
NodeHash_84e35c0.inputs.template = 'sub-01/anat/sub-01_T1w.nii.gz'
NodeHash_84e35c0.inputs.anon = True
NodeHash_84e35c0.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_84e35c0.inputs.local_directory = '/tmp'

#Wraps command **N4BiasFieldCorrection**
NodeHash_fff29c0 = pe.Node(interface = ants.N4BiasFieldCorrection(), name = 'NodeName_fff29c0')
NodeHash_fff29c0.inputs.save_bias = True
NodeHash_fff29c0.inputs.copy_header = False
NodeHash_fff29c0.inputs.dimension = 3
NodeHash_fff29c0.inputs.num_threads = 4

#Wraps command **3dUnifize**
NodeHash_f966e70 = pe.Node(interface = afni.Unifize(), name = 'NodeName_f966e70')
NodeHash_f966e70.inputs.outputtype = 'NIFTI_GZ'

#Wraps command **3dSkullStrip**
NodeHash_132bc280 = pe.Node(interface = afni.SkullStrip(), name = 'NodeName_132bc280')
NodeHash_132bc280.inputs.outputtype = 'NIFTI_GZ'

#Wraps command **3dcalc**
NodeHash_14d89eb0 = pe.Node(interface = afni.Calc(), name = 'NodeName_14d89eb0')
NodeHash_14d89eb0.inputs.expr = 'a*step(b)'
NodeHash_14d89eb0.inputs.outputtype = 'NIFTI_GZ'

#Wraps command **fslmaths**
NodeHash_1758c760 = pe.Node(interface = fsl.Threshold(), name = 'NodeName_1758c760')
NodeHash_1758c760.inputs.thresh = 1.e-3
NodeHash_1758c760.inputs.args = '-bin'

#Wraps command **3dUnifize**
NodeHash_14c85ce0 = pe.Node(interface = afni.Unifize(), name = 'NodeName_14c85ce0')
NodeHash_14c85ce0.inputs.gm = True
NodeHash_14c85ce0.inputs.outputtype = 'NIFTI_GZ'

#Generic datasink module to store structured outputs
NodeHash_11a54520 = pe.Node(interface = io.DataSink(), name = 'NodeName_11a54520')
NodeHash_11a54520.inputs.base_directory = '/tmp'

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_14c85ce0, 'out_file', NodeHash_11a54520, 'out_file')
analysisflow.connect(NodeHash_1758c760, 'out_file', NodeHash_11a54520, 'out_mask')
analysisflow.connect(NodeHash_14d89eb0, 'out_file', NodeHash_14c85ce0, 'in_file')
analysisflow.connect(NodeHash_14d89eb0, 'out_file', NodeHash_1758c760, 'in_file')
analysisflow.connect(NodeHash_132bc280, 'out_file', NodeHash_14d89eb0, 'in_file_b')
analysisflow.connect(NodeHash_f966e70, 'out_file', NodeHash_14d89eb0, 'in_file_a')
analysisflow.connect(NodeHash_fff29c0, 'bias_image', NodeHash_11a54520, 'bias_image')
analysisflow.connect(NodeHash_f966e70, 'out_file', NodeHash_132bc280, 'in_file')
analysisflow.connect(NodeHash_fff29c0, 'output_image', NodeHash_f966e70, 'in_file')
analysisflow.connect(NodeHash_84e35c0, 'outfiles', NodeHash_fff29c0, 'input_image')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 1} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
