#This is a Nipype generator. Warning, here be dragons.
import sys
import nipype
import nipype.pipeline as pe
import nipype.interfaces.io as io
import nipype.interfaces.fsl as fsl
import nipype.algorithms.confounds as confounds

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Generic datagrabber module that wraps around glob in an
NodeHash_30f69e0 = pe.Node(io.S3DataGrabber(outfields=['outfiles']), name = 'NodeName_30f69e0')
NodeHash_30f69e0.inputs.bucket = 'openneuro'
NodeHash_30f69e0.inputs.sort_filelist = True
NodeHash_30f69e0.inputs.template = 'sub-01/func/sub-01_task-simon_run-1_bold.nii.gz'
NodeHash_30f69e0.inputs.anon = True
NodeHash_30f69e0.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_30f69e0.inputs.local_directory = '/tmp'

#Wraps command **slicetimer**
NodeHash_1d000c0 = pe.Node(interface = fsl.SliceTimer(), name = 'NodeName_1d000c0')

#Wraps command **mcflirt**
NodeHash_22f2e80 = pe.Node(interface = fsl.MCFLIRT(), name = 'NodeName_22f2e80')

#Computes the time-course SNR for a time series
NodeHash_50c02c0 = pe.Node(interface = confounds.TSNR(), name = 'NodeName_50c02c0')
NodeHash_50c02c0.inputs.regress_poly = 3

#Wraps command **fslstats**
NodeHash_3ac27f0 = pe.Node(interface = fsl.ImageStats(), name = 'NodeName_3ac27f0')
NodeHash_3ac27f0.inputs.op_string = '-p 98'

#Wraps command **fslmaths**
NodeHash_30f6760 = pe.Node(interface = fsl.Threshold(), name = 'NodeName_30f6760')
NodeHash_30f6760.inputs.args = '-bin'

#Anatomical compcor: for inputs and outputs, see CompCor.
NodeHash_325da10 = pe.Node(interface = confounds.ACompCor(), name = 'NodeName_325da10')
NodeHash_325da10.inputs.num_components = 2

#Wraps command **fsl_regfilt**
NodeHash_430d1e0 = pe.Node(interface = fsl.FilterRegressor(), name = 'NodeName_430d1e0')
NodeHash_430d1e0.inputs.filter_columns = [1, 2]

#Wraps command **fslmaths**
NodeHash_77e3220 = pe.Node(interface = fsl.TemporalFilter(), name = 'NodeName_77e3220')
NodeHash_77e3220.inputs.highpass_sigma = 25

#Generic datasink module to store structured outputs
NodeHash_99576b0 = pe.Node(interface = io.DataSink(), name = 'NodeName_99576b0')

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_30f69e0, 'outfiles', NodeHash_1d000c0, 'in_file')
analysisflow.connect(NodeHash_1d000c0, 'slice_time_corrected_file', NodeHash_22f2e80, 'in_file')
analysisflow.connect(NodeHash_22f2e80, 'out_file', NodeHash_50c02c0, 'in_file')
analysisflow.connect(NodeHash_50c02c0, 'stddev_file', NodeHash_3ac27f0, 'in_file')
analysisflow.connect(NodeHash_3ac27f0, 'out_stat', NodeHash_30f6760, 'thresh')
analysisflow.connect(NodeHash_22f2e80, 'out_file', NodeHash_325da10, 'realigned_file')
analysisflow.connect(NodeHash_30f6760, 'out_file', NodeHash_325da10, 'mask_files')
analysisflow.connect(NodeHash_325da10, 'components_file', NodeHash_430d1e0, 'design_file')
analysisflow.connect(NodeHash_50c02c0, 'detrended_file', NodeHash_430d1e0, 'in_file')
analysisflow.connect(NodeHash_430d1e0, 'out_file', NodeHash_77e3220, 'in_file')
analysisflow.connect(NodeHash_77e3220, 'out_file', NodeHash_99576b0, 'filtered_file')
analysisflow.connect(NodeHash_50c02c0, 'stddev_file', NodeHash_30f6760, 'in_file')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 1} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
