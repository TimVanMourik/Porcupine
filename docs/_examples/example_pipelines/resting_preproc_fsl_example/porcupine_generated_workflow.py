#This is a Nipype generator. Warning, here be dragons.
import sys
import nipype
import nipype.pipeline as pe
import nipype.interfaces.io as io
import nipype.interfaces.fsl as fsl
import nipype.algorithms.confounds as confounds

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Generic datagrabber module that wraps around glob in an
NodeHash_a58c180 = pe.Node(io.S3DataGrabber(outfields=['outfiles']), name = 'NodeName_a58c180')
NodeHash_a58c180.inputs.bucket = 'openneuro'
NodeHash_a58c180.inputs.sort_filelist = True
NodeHash_a58c180.inputs.template = 'sub-01/func/sub-01_task-simon_run-1_bold.nii.gz'
NodeHash_a58c180.inputs.anon = True
NodeHash_a58c180.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_a58c180.inputs.local_directory = '/tmp'

#Wraps command **slicetimer**
NodeHash_10a02a50 = pe.Node(interface = fsl.SliceTimer(), name = 'NodeName_10a02a50')

#Wraps command **mcflirt**
NodeHash_9648590 = pe.Node(interface = fsl.MCFLIRT(), name = 'NodeName_9648590')

#Computes the time-course SNR for a time series
NodeHash_56e61f0 = pe.Node(interface = confounds.TSNR(), name = 'NodeName_56e61f0')
NodeHash_56e61f0.inputs.regress_poly = 3

#Wraps command **fslstats**
NodeHash_3a410a0 = pe.Node(interface = fsl.ImageStats(), name = 'NodeName_3a410a0')
NodeHash_3a410a0.inputs.op_string = '-p 98'

#Wraps command **fslmaths**
NodeHash_3af3250 = pe.Node(interface = fsl.Threshold(), name = 'NodeName_3af3250')
NodeHash_3af3250.inputs.args = '-bin'

#Anatomical compcor: for inputs and outputs, see CompCor.
NodeHash_65bfd70 = pe.Node(interface = confounds.ACompCor(), name = 'NodeName_65bfd70')
NodeHash_65bfd70.inputs.num_components = 2

#Wraps command **fsl_regfilt**
NodeHash_7bf7eb0 = pe.Node(interface = fsl.FilterRegressor(), name = 'NodeName_7bf7eb0')
NodeHash_7bf7eb0.inputs.filter_columns = [1, 2]

#Wraps command **fslmaths**
NodeHash_7c09350 = pe.Node(interface = fsl.TemporalFilter(), name = 'NodeName_7c09350')
NodeHash_7c09350.inputs.highpass_sigma = 25

#Generic datasink module to store structured outputs
NodeHash_ab72900 = pe.Node(interface = io.DataSink(), name = 'NodeName_ab72900')

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_56e61f0, 'stddev_file', NodeHash_3af3250, 'in_file')
analysisflow.connect(NodeHash_7c09350, 'out_file', NodeHash_ab72900, 'filtered_file')
analysisflow.connect(NodeHash_7bf7eb0, 'out_file', NodeHash_7c09350, 'in_file')
analysisflow.connect(NodeHash_56e61f0, 'detrended_file', NodeHash_7bf7eb0, 'in_file')
analysisflow.connect(NodeHash_65bfd70, 'components_file', NodeHash_7bf7eb0, 'design_file')
analysisflow.connect(NodeHash_3af3250, 'out_file', NodeHash_65bfd70, 'mask_files')
analysisflow.connect(NodeHash_9648590, 'out_file', NodeHash_65bfd70, 'realigned_file')
analysisflow.connect(NodeHash_3a410a0, 'out_stat', NodeHash_3af3250, 'thresh')
analysisflow.connect(NodeHash_56e61f0, 'stddev_file', NodeHash_3a410a0, 'in_file')
analysisflow.connect(NodeHash_9648590, 'out_file', NodeHash_56e61f0, 'in_file')
analysisflow.connect(NodeHash_10a02a50, 'slice_time_corrected_file', NodeHash_9648590, 'in_file')
analysisflow.connect(NodeHash_a58c180, 'outfiles', NodeHash_10a02a50, 'in_file')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 1} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
