#This is a Nipype generator. Warning, here be dragons.
import sys
import nipype
import nipype.pipeline as pe
import nipype.interfaces.io as io
sys.path.append('/media/lukas/goliath/Porcupine/example_workflows/firstlevel_fsl_and_custom_modules_example')
import firstlevelhelpers
import nipype.interfaces.fsl as fsl
import nipype.algorithms.modelgen as modelgen

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Generic datagrabber module that wraps around glob in an
NodeHash_3174ca0 = pe.Node(io.S3DataGrabber(outfields=['outfiles']), name = 'NodeName_3174ca0')
NodeHash_3174ca0.inputs.anon = True
NodeHash_3174ca0.inputs.bucket = 'openneuro'
NodeHash_3174ca0.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_3174ca0.inputs.local_directory = '/tmp'
NodeHash_3174ca0.inputs.sort_filelist = True
NodeHash_3174ca0.inputs.template = 'sub-01/func/sub-01_task-simon_run-1_bold.nii.gz'

#Generic datagrabber module that wraps around glob in an
NodeHash_436e8b0 = pe.Node(io.S3DataGrabber(outfields=['events']), name = 'NodeName_436e8b0')
NodeHash_436e8b0.inputs.anon = True
NodeHash_436e8b0.inputs.bucket = 'openneuro'
NodeHash_436e8b0.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_436e8b0.inputs.local_directory = '/tmp'
NodeHash_436e8b0.inputs.sort_filelist = True
NodeHash_436e8b0.inputs.template = 'sub-01/func/sub-01_task-simon_run-1_events.tsv'

#Custom interface wrapping function Tsv2subjectinfo
NodeHash_1aa42a0 = pe.Node(interface = firstlevelhelpers.Tsv2subjectinfo, name = 'NodeName_1aa42a0')

#Wraps command **bet**
NodeHash_43b3e40 = pe.Node(interface = fsl.BET(), name = 'NodeName_43b3e40')
NodeHash_43b3e40.inputs.frac = 0.3
NodeHash_43b3e40.inputs.mask = True
NodeHash_43b3e40.inputs.no_output = True

#Wraps command **fslmaths**
NodeHash_59fb370 = pe.Node(interface = fsl.ApplyMask(), name = 'NodeName_59fb370')

#Wraps command **film_gls**
NodeHash_995eb40 = pe.Node(interface = fsl.FILMGLS(), name = 'NodeName_995eb40')

#Makes a model specification compatible with spm/fsl designers.
NodeHash_6633130 = pe.Node(interface = modelgen.SpecifyModel(), name = 'NodeName_6633130')
NodeHash_6633130.inputs.high_pass_filter_cutoff = 0
NodeHash_6633130.inputs.input_units = 'secs'
NodeHash_6633130.inputs.time_repetition = 2.0

#Generic datasink module to store structured outputs
NodeHash_9db6310 = pe.Node(interface = io.DataSink(), name = 'NodeName_9db6310')
NodeHash_9db6310.inputs.base_directory = '/tmp/FIRSTLEVEL'

#Generate FEAT specific files
NodeHash_884abd0 = pe.Node(interface = fsl.Level1Design(), name = 'NodeName_884abd0')
NodeHash_884abd0.inputs.bases = {'dgamma':{'derivs': False}}
NodeHash_884abd0.inputs.contrasts = [('con-incon', 'T', ['congruent_correct', 'congruent_correct'], [-1, 1])]
NodeHash_884abd0.inputs.interscan_interval = 2.0
NodeHash_884abd0.inputs.model_serial_correlations = True

#Wraps command **feat_model**
NodeHash_8a87ec0 = pe.Node(interface = fsl.FEATModel(), name = 'NodeName_8a87ec0')

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_3174ca0, 'outfiles', NodeHash_43b3e40, 'in_file')
analysisflow.connect(NodeHash_436e8b0, 'events', NodeHash_1aa42a0, 'in_file')
analysisflow.connect(NodeHash_3174ca0, 'outfiles', NodeHash_59fb370, 'in_file')
analysisflow.connect(NodeHash_1aa42a0, 'subject_info', NodeHash_6633130, 'subject_info')
analysisflow.connect(NodeHash_6633130, 'session_info', NodeHash_884abd0, 'session_info')
analysisflow.connect(NodeHash_884abd0, 'fsf_files', NodeHash_8a87ec0, 'fsf_file')
analysisflow.connect(NodeHash_884abd0, 'ev_files', NodeHash_8a87ec0, 'ev_files')
analysisflow.connect(NodeHash_8a87ec0, 'con_file', NodeHash_995eb40, 'tcon_file')
analysisflow.connect(NodeHash_8a87ec0, 'design_file', NodeHash_995eb40, 'design_file')
analysisflow.connect(NodeHash_995eb40, 'results_dir', NodeHash_9db6310, 'firstlevel')
analysisflow.connect(NodeHash_43b3e40, 'mask_file', NodeHash_59fb370, 'mask_file')
analysisflow.connect(NodeHash_59fb370, 'out_file', NodeHash_6633130, 'functional_runs')
analysisflow.connect(NodeHash_59fb370, 'out_file', NodeHash_995eb40, 'in_file')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 1} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
