#This is a Nipype generator. Warning, here be dragons.
import sys
import nipype
import nipype.pipeline as pe
import nipype.interfaces.io as io
import nipype.interfaces.fsl as fsl
import nipype.algorithms.confounds as confounds

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Generic datagrabber module that wraps around glob in an
NodeHash_f967c10 = pe.Node(io.S3DataGrabber(outfields=['outfiles']), name = 'NodeName_f967c10')
NodeHash_f967c10.inputs.bucket = 'openneuro'
NodeHash_f967c10.inputs.sort_filelist = True
NodeHash_f967c10.inputs.template = 'sub-01/func/sub-01_task-simon_run-1_bold.nii.gz'
NodeHash_f967c10.inputs.anon = True
NodeHash_f967c10.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_f967c10.inputs.local_directory = '/tmp'

#Wraps command **slicetimer**
NodeHash_1b357220 = pe.Node(interface = fsl.SliceTimer(), name = 'NodeName_1b357220')

#Wraps command **mcflirt**
NodeHash_1b961070 = pe.Node(interface = fsl.MCFLIRT(), name = 'NodeName_1b961070')

#Computes the time-course SNR for a time series
NodeHash_203cd2f0 = pe.Node(interface = confounds.TSNR(), name = 'NodeName_203cd2f0')
NodeHash_203cd2f0.inputs.regress_poly = 2

#Wraps command **fslstats**
NodeHash_1e7acf80 = pe.Node(interface = fsl.ImageStats(), name = 'NodeName_1e7acf80')
NodeHash_1e7acf80.inputs.op_string = '-p 98'

#Wraps command **fslmaths**
NodeHash_1d00edc0 = pe.Node(interface = fsl.Threshold(), name = 'NodeName_1d00edc0')

#Anatomical compcor: for inputs and outputs, see CompCor.
NodeHash_1d3982c0 = pe.Node(interface = confounds.ACompCor(), name = 'NodeName_1d3982c0')
NodeHash_1d3982c0.inputs.num_components = 3

#Wraps command **fsl_regfilt**
NodeHash_23e60ee0 = pe.Node(interface = fsl.FilterRegressor(), name = 'NodeName_23e60ee0')
NodeHash_23e60ee0.inputs.filter_columns = [1, 2]

#Wraps command **fslmaths**
NodeHash_23e6e8c0 = pe.Node(interface = fsl.TemporalFilter(), name = 'NodeName_23e6e8c0')
NodeHash_23e6e8c0.inputs.lowpass_sigma = 3

#Generic datasink module to store structured outputs
NodeHash_23e9e530 = pe.Node(interface = io.DataSink(), name = 'NodeName_23e9e530')
NodeHash_23e9e530.inputs.base_directory = '/tmp'

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_23e6e8c0, 'out_file', NodeHash_23e9e530, 'rs_clean')
analysisflow.connect(NodeHash_23e60ee0, 'out_file', NodeHash_23e6e8c0, 'in_file')
analysisflow.connect(NodeHash_203cd2f0, 'detrended_file', NodeHash_23e60ee0, 'in_file')
analysisflow.connect(NodeHash_1d3982c0, 'components_file', NodeHash_23e60ee0, 'design_file')
analysisflow.connect(NodeHash_1b357220, 'slice_time_corrected_file', NodeHash_1d3982c0, 'realigned_file')
analysisflow.connect(NodeHash_1d00edc0, 'out_file', NodeHash_1d3982c0, 'mask_files')
analysisflow.connect(NodeHash_203cd2f0, 'stddev_file', NodeHash_1d00edc0, 'in_file')
analysisflow.connect(NodeHash_1e7acf80, 'out_stat', NodeHash_1d00edc0, 'thresh')
analysisflow.connect(NodeHash_203cd2f0, 'stddev_file', NodeHash_1e7acf80, 'in_file')
analysisflow.connect(NodeHash_1b961070, 'out_file', NodeHash_203cd2f0, 'in_file')
analysisflow.connect(NodeHash_1b357220, 'slice_time_corrected_file', NodeHash_1b961070, 'in_file')
analysisflow.connect(NodeHash_f967c10, 'outfiles', NodeHash_1b357220, 'in_file')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 1} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
