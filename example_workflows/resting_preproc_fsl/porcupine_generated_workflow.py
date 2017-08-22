#This is a NiPype generator. Warning, here be dragons.
import nipype
import nipype.pipeline as pe
import nipype.interfaces.io as io
import nipype.interfaces.fsl as fsl
import nipype.algorithms.confounds as confounds

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Generic datagrabber module that wraps around glob in an
NodeHash_2f40f80 = pe.Node(io.S3DataGrabber(outfields=['outfiles']), name = 'NodeName_2f40f80')
NodeHash_2f40f80.inputs.anon = True
NodeHash_2f40f80.inputs.bucket = 'openneuro'
NodeHash_2f40f80.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_2f40f80.inputs.local_directory = '/tmp'
NodeHash_2f40f80.inputs.sort_filelist = True
NodeHash_2f40f80.inputs.template = 'sub-01/func/sub-01_task-simon_run-1_bold.nii.gz'

#Wraps command **slicetimer**
NodeHash_258f950 = pe.Node(interface = fsl.SliceTimer(), name = 'NodeName_258f950')

#Wraps command **mcflirt**
NodeHash_40a99f0 = pe.Node(interface = fsl.MCFLIRT(), name = 'NodeName_40a99f0')

#Computes the time-course SNR for a time series
NodeHash_5e7db90 = pe.Node(interface = confounds.TSNR(), name = 'NodeName_5e7db90')
NodeHash_5e7db90.inputs.regress_poly = 2

#Wraps command **fslstats**
NodeHash_2c4d280 = pe.Node(interface = fsl.ImageStats(), name = 'NodeName_2c4d280')
NodeHash_2c4d280.inputs.op_string = '-p 98'

#Wraps command **fslmaths**
NodeHash_38a9b60 = pe.Node(interface = fsl.Threshold(), name = 'NodeName_38a9b60')

#Anatomical compcor: for inputs and outputs, see CompCor.
NodeHash_5e38960 = pe.Node(interface = confounds.ACompCor(), name = 'NodeName_5e38960')
NodeHash_5e38960.inputs.num_components = 3

#Wraps command **fsl_regfilt**
NodeHash_9ee9f70 = pe.Node(interface = fsl.FilterRegressor(), name = 'NodeName_9ee9f70')
NodeHash_9ee9f70.inputs.filter_columns = [1, 2]

#Wraps command **fslmaths**
NodeHash_addaf50 = pe.Node(interface = fsl.TemporalFilter(), name = 'NodeName_addaf50')

#Generic datasink module to store structured outputs
NodeHash_38bd8e0 = pe.Node(interface = io.DataSink(), name = 'NodeName_38bd8e0')
NodeHash_38bd8e0.inputs.base_directory = '/tmp'

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_5e38960, 'components_file', NodeHash_9ee9f70, 'design_file')
analysisflow.connect(NodeHash_addaf50, 'out_file', NodeHash_38bd8e0, 'filtered_file')
analysisflow.connect(NodeHash_9ee9f70, 'out_file', NodeHash_addaf50, 'in_file')
analysisflow.connect(NodeHash_5e7db90, 'detrended_file', NodeHash_9ee9f70, 'in_file')
analysisflow.connect(NodeHash_38a9b60, 'out_file', NodeHash_5e38960, 'mask_files')
analysisflow.connect(NodeHash_40a99f0, 'out_file', NodeHash_5e38960, 'realigned_file')
analysisflow.connect(NodeHash_2c4d280, 'out_stat', NodeHash_38a9b60, 'thresh')
analysisflow.connect(NodeHash_5e7db90, 'stddev_file', NodeHash_2c4d280, 'in_file')
analysisflow.connect(NodeHash_5e7db90, 'stddev_file', NodeHash_38a9b60, 'in_file')
analysisflow.connect(NodeHash_40a99f0, 'out_file', NodeHash_5e7db90, 'in_file')
analysisflow.connect(NodeHash_258f950, 'slice_time_corrected_file', NodeHash_40a99f0, 'in_file')
analysisflow.connect(NodeHash_2f40f80, 'outfiles', NodeHash_258f950, 'in_file')

#Run the workflow
analysisflow.run()
