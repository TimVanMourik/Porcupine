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
NodeHash_968bcf0 = pe.Node(io.S3DataGrabber(outfields=['outfiles']), name = 'NodeName_968bcf0')
NodeHash_968bcf0.inputs.anon = True
NodeHash_968bcf0.inputs.bucket = 'openneuro'
NodeHash_968bcf0.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_968bcf0.inputs.local_directory = '/tmp'
NodeHash_968bcf0.inputs.sort_filelist = True
NodeHash_968bcf0.inputs.template = 'sub-01/anat/sub-01_T1w.nii.gz'

#Wraps command **N4BiasFieldCorrection**
NodeHash_a6598a0 = pe.Node(interface = ants.N4BiasFieldCorrection(), name = 'NodeName_a6598a0')
NodeHash_a6598a0.inputs.copy_header = False
NodeHash_a6598a0.inputs.dimension = 3
NodeHash_a6598a0.inputs.num_threads = 4
NodeHash_a6598a0.inputs.save_bias = True

#Wraps command **3dUnifize**
NodeHash_b1e08e0 = pe.Node(interface = afni.Unifize(), name = 'NodeName_b1e08e0')
NodeHash_b1e08e0.inputs.outputtype = 'NIFTI_GZ'

#Wraps command **3dSkullStrip**
NodeHash_c4a8f30 = pe.Node(interface = afni.SkullStrip(), name = 'NodeName_c4a8f30')
NodeHash_c4a8f30.inputs.outputtype = 'NIFTI_GZ'

#Wraps command **3dcalc**
NodeHash_c4b9fe0 = pe.Node(interface = afni.Calc(), name = 'NodeName_c4b9fe0')
NodeHash_c4b9fe0.inputs.expr = 'a*step(b)'
NodeHash_c4b9fe0.inputs.outputtype = 'NIFTI_GZ'

#Wraps command **fslmaths**
NodeHash_de2b130 = pe.Node(interface = fsl.Threshold(), name = 'NodeName_de2b130')
NodeHash_de2b130.inputs.args = '-bin'
NodeHash_de2b130.inputs.thresh = 1.e-3

#Wraps command **3dUnifize**
NodeHash_efa3a60 = pe.Node(interface = afni.Unifize(), name = 'NodeName_efa3a60')
NodeHash_efa3a60.inputs.gm = True
NodeHash_efa3a60.inputs.outputtype = 'NIFTI_GZ'

#Generic datasink module to store structured outputs
NodeHash_f05fdf0 = pe.Node(interface = io.DataSink(), name = 'NodeName_f05fdf0')
NodeHash_f05fdf0.inputs.base_directory = '/tmp'

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_968bcf0, 'outfiles', NodeHash_a6598a0, 'input_image')
analysisflow.connect(NodeHash_a6598a0, 'output_image', NodeHash_b1e08e0, 'in_file')
analysisflow.connect(NodeHash_b1e08e0, 'out_file', NodeHash_c4a8f30, 'in_file')
analysisflow.connect(NodeHash_a6598a0, 'bias_image', NodeHash_f05fdf0, 'bias_image')
analysisflow.connect(NodeHash_b1e08e0, 'out_file', NodeHash_c4b9fe0, 'in_file_a')
analysisflow.connect(NodeHash_c4a8f30, 'out_file', NodeHash_c4b9fe0, 'in_file_b')
analysisflow.connect(NodeHash_c4b9fe0, 'out_file', NodeHash_de2b130, 'in_file')
analysisflow.connect(NodeHash_c4b9fe0, 'out_file', NodeHash_efa3a60, 'in_file')
analysisflow.connect(NodeHash_de2b130, 'out_file', NodeHash_f05fdf0, 'out_mask')
analysisflow.connect(NodeHash_efa3a60, 'out_file', NodeHash_f05fdf0, 'out_file')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 1} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
