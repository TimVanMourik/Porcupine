#This is a Nipype generator. Warning, here be dragons.
import sys
import nipype
import nipype.pipeline as pe
import nipype.interfaces.io as io
import nipype.interfaces.fsl as fsl
import firstlevelhelpers
import nipype.algorithms.modelgen as modelgen

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Generic datagrabber module that wraps around glob in an
NodeHash_32c4e30 = pe.Node(io.S3DataGrabber(infields=['field_template'], outfields=['func','events']), name = 'NodeName_32c4e30')
NodeHash_32c4e30.inputs.anon = True
NodeHash_32c4e30.inputs.bucket = 'openneuro'
NodeHash_32c4e30.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_32c4e30.inputs.local_directory = '/tmp'
NodeHash_32c4e30.inputs.sort_filelist = True
NodeHash_32c4e30.inputs.template = '*'
NodeHash_32c4e30.inputs.template_args = dict(func=[['bold.nii.gz']], events=[['events.tsv']])
NodeHash_32c4e30.inputs.field_template = dict(func='sub-01/func/sub-01_task-simon_run-1_%s', events='sub-01/func/sub-01_task-simon_run-1_%s')

#Wraps command **bet**
NodeHash_3443a20 = pe.Node(interface = fsl.BET(), name = 'NodeName_3443a20')
NodeHash_3443a20.inputs.frac = 0.3
NodeHash_3443a20.inputs.mask = True
NodeHash_3443a20.inputs.no_output = True

#Wraps command **fslmaths**
NodeHash_43b01b0 = pe.Node(interface = fsl.ApplyMask(), name = 'NodeName_43b01b0')

#Custom interface wrapping function Tsv2subjectinfo
NodeHash_3042f20 = pe.Node(interface = firstlevelhelpers.Tsv2subjectinfo, name = 'NodeName_3042f20')

#Makes a model specification compatible with spm/fsl designers.
NodeHash_6bef320 = pe.Node(interface = modelgen.SpecifyModel(), name = 'NodeName_6bef320')
NodeHash_6bef320.inputs.high_pass_filter_cutoff = 0
NodeHash_6bef320.inputs.input_units = 'secs'
NodeHash_6bef320.inputs.time_repetition = 2.0

#Generate FEAT specific files
NodeHash_8241250 = pe.Node(interface = fsl.Level1Design(), name = 'NodeName_8241250')
NodeHash_8241250.inputs.bases = {'dgamma':{'derivs': False}}
NodeHash_8241250.inputs.contrasts = [('con-incon', 'T', ['congruent_correct', 'congruent_correct'], [-1, 1])]
NodeHash_8241250.inputs.interscan_interval = 2.0
NodeHash_8241250.inputs.model_serial_correlations = True

#Wraps command **feat_model**
NodeHash_8b12580 = pe.Node(interface = fsl.FEATModel(), name = 'NodeName_8b12580')

#Wraps command **film_gls**
NodeHash_5015c80 = pe.Node(interface = fsl.FILMGLS(), name = 'NodeName_5015c80')

#Generic datasink module to store structured outputs
NodeHash_8a104d0 = pe.Node(interface = io.DataSink(), name = 'NodeName_8a104d0')
NodeHash_8a104d0.inputs.base_directory = '/tmp/FIRSTLEVEL'

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_3042f20, 'subject_info', NodeHash_6bef320, 'subject_info')
analysisflow.connect(NodeHash_32c4e30, 'events', NodeHash_3042f20, 'in_file')
analysisflow.connect(NodeHash_6bef320, 'session_info', NodeHash_8241250, 'session_info')
analysisflow.connect(NodeHash_8241250, 'fsf_files', NodeHash_8b12580, 'fsf_file')
analysisflow.connect(NodeHash_8241250, 'ev_files', NodeHash_8b12580, 'ev_files')
analysisflow.connect(NodeHash_8b12580, 'con_file', NodeHash_5015c80, 'tcon_file')
analysisflow.connect(NodeHash_8b12580, 'design_file', NodeHash_5015c80, 'design_file')
analysisflow.connect(NodeHash_5015c80, 'results_dir', NodeHash_8a104d0, 'firstlevel')
analysisflow.connect(NodeHash_3443a20, 'mask_file', NodeHash_43b01b0, 'mask_file')
analysisflow.connect(NodeHash_43b01b0, 'out_file', NodeHash_6bef320, 'functional_runs')
analysisflow.connect(NodeHash_43b01b0, 'out_file', NodeHash_5015c80, 'in_file')
analysisflow.connect(NodeHash_32c4e30, 'func', NodeHash_3443a20, 'in_file')
analysisflow.connect(NodeHash_32c4e30, 'func', NodeHash_43b01b0, 'in_file')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 1} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
