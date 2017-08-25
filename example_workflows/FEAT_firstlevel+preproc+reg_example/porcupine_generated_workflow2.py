#This is a Nipype generator. Warning, here be dragons.
import sys
import nipype
import nipype.pipeline as pe
import nipype.interfaces.utility as utility
import nipype.interfaces.io as io
import nipype.interfaces.fsl as fsl
sys.path.append('/media/lukas/goliath/Porcupine/example_workflows/firstlevel')
import firstlevelhelpers
import nipype.algorithms.modelgen as modelgen

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Basic interface class generates identity mappings
NodeHash_64138c50 = pe.Node(utility.IdentityInterface(fields=['sub_id']), name = 'NodeName_64138c50')
NodeHash_64138c50.inputs.sub_id = 'sub-02'

#Flexibly collect data from disk to feed into workflows.
NodeHash_643355b0 = pe.Node(io.SelectFiles(templates={'func':'{sub_id}/func/{sub_id}_task-simon_run-1_bold.nii.gz','anat':'{sub_id}/anat/{sub_id}_T1w.nii.gz','events':'{sub_id}/func/{sub_id}_task-simon_run-1_events.tsv'}), name = 'NodeName_643355b0')
NodeHash_643355b0.inputs.base_directory = '/media/lukas/goliath/Porcupine/example_workflows/example_data'
NodeHash_643355b0.inputs.sort_filelist = True

#Generic datagrabber module that wraps around glob in an
NodeHash_41b41c0 = pe.Node(io.S3DataGrabber(outfields=['outfiles']), name = 'NodeName_41b41c0')
NodeHash_41b41c0.inputs.bucket = 'openneuro'
NodeHash_41b41c0.inputs.sort_filelist = True
NodeHash_41b41c0.inputs.template = 'sub-01/func/sub-01_task-simon_run-1_bold.nii.gz'
NodeHash_41b41c0.inputs.anon = True
NodeHash_41b41c0.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_41b41c0.inputs.local_directory = '/tmp'

#Generic datagrabber module that wraps around glob in an
NodeHash_1c7d6a60 = pe.Node(io.S3DataGrabber(outfields=['outfiles']), name = 'NodeName_1c7d6a60')
NodeHash_1c7d6a60.inputs.bucket = 'openneuro'
NodeHash_1c7d6a60.inputs.sort_filelist = True
NodeHash_1c7d6a60.inputs.template = 'sub-01/anat/sub-01_T1w.nii.gz'
NodeHash_1c7d6a60.inputs.anon = True
NodeHash_1c7d6a60.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_1c7d6a60.inputs.local_directory = '/tmp'

#Generic datagrabber module that wraps around glob in an
NodeHash_28ac7da0 = pe.Node(io.S3DataGrabber(outfields=['events']), name = 'NodeName_28ac7da0')
NodeHash_28ac7da0.inputs.bucket = 'openneuro'
NodeHash_28ac7da0.inputs.sort_filelist = True
NodeHash_28ac7da0.inputs.template = 'sub-01/func/sub-01_task-simon_run-1_events.tsv'
NodeHash_28ac7da0.inputs.anon = True
NodeHash_28ac7da0.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_28ac7da0.inputs.local_directory = '/tmp'

#Basic interface class generates identity mappings
NodeHash_30cfe660 = pe.Node(utility.IdentityInterface(fields=['MNI_head','MNI_brain','MNI_mask']), name = 'NodeName_30cfe660')
NodeHash_30cfe660.inputs.MNI_head = '/usr/share/fsl/5.0/data/standard/MNI152_T1_2mm.nii.gz'
NodeHash_30cfe660.inputs.MNI_brain = '/usr/share/fsl/5.0/data/standard/MNI152_T1_2mm_brain.nii.gz'
NodeHash_30cfe660.inputs.MNI_mask = '/usr/share/fsl/5.0/data/standard/MNI152_T1_2mm_brain_mask_dil.nii.gz'

#Wraps command **bet**
NodeHash_2b027090 = pe.Node(interface = fsl.BET(), name = 'NodeName_2b027090')
NodeHash_2b027090.inputs.frac = 0.3
NodeHash_2b027090.inputs.robust = True

#Wraps command **fast**
NodeHash_27d1f090 = pe.Node(interface = fsl.FAST(), name = 'NodeName_27d1f090')

#Basic interface class to select specific elements from a list
NodeHash_31fd8990 = pe.Node(interface = utility.Select(), name = 'NodeName_31fd8990')
NodeHash_31fd8990.inputs.index = 2

#Wraps command **fslmaths**
NodeHash_30cfd500 = pe.Node(interface = fsl.Threshold(), name = 'NodeName_30cfd500')
NodeHash_30cfd500.inputs.thresh = 0.5
NodeHash_30cfd500.inputs.args = '-bin'

#Wraps command **flirt**
NodeHash_2db5da50 = pe.Node(interface = fsl.FLIRT(), name = 'NodeName_2db5da50')
NodeHash_2db5da50.inputs.cost = 'corratio'
NodeHash_2db5da50.inputs.dof = 12
NodeHash_2db5da50.inputs.no_resample = True
NodeHash_2db5da50.inputs.searchr_x = [-90, 90]
NodeHash_2db5da50.inputs.searchr_y = [-90, 90]
NodeHash_2db5da50.inputs.searchr_z = [-90, 90]

#Wraps command **fnirt**
NodeHash_34338fc0 = pe.Node(interface = fsl.FNIRT(), name = 'NodeName_34338fc0')
NodeHash_34338fc0.inputs.config_file = 'T1_2_MNI152_2mm'
NodeHash_34338fc0.inputs.warp_resolution = (10, 10, 10)

#Wraps command **fslroi**
NodeHash_2cc3ef00 = pe.Node(interface = fsl.ExtractROI(), name = 'NodeName_2cc3ef00')
NodeHash_2cc3ef00.inputs.t_min = 1
NodeHash_2cc3ef00.inputs.t_size = 1

#Wraps command **flirt**
NodeHash_379184b0 = pe.Node(interface = fsl.FLIRT(), name = 'NodeName_379184b0')

#Wraps command **flirt**
NodeHash_31e5e3a0 = pe.Node(interface = fsl.FLIRT(), name = 'NodeName_31e5e3a0')
NodeHash_31e5e3a0.inputs.cost = 'bbr'
NodeHash_31e5e3a0.inputs.dof = 6
NodeHash_31e5e3a0.inputs.no_resample = True

#Wraps command **convert_xfm**
NodeHash_433f9c80 = pe.Node(interface = fsl.ConvertXFM(), name = 'NodeName_433f9c80')
NodeHash_433f9c80.inputs.concat_xfm = True

#Wraps command **mcflirt**
NodeHash_410f2c90 = pe.Node(interface = fsl.MCFLIRT(), name = 'NodeName_410f2c90')
NodeHash_410f2c90.inputs.interpolation = 'spline'
NodeHash_410f2c90.inputs.save_mats = True
NodeHash_410f2c90.inputs.save_plots = True
NodeHash_410f2c90.inputs.save_rms = True

#Wraps command **fsl_tsplot**
NodeHash_3c666410 = pe.Node(interface = fsl.PlotMotionParams(), name = 'NodeName_3c666410')
NodeHash_3c666410.inputs.in_source = 'fsl'
NodeHash_3c666410.inputs.args = '-a x,y,z -w 640 -h 144'
NodeHash_3c666410.iterables = [('plot_type', ['rotations', 'translations'])]

#Wraps command **slicetimer**
NodeHash_31719d90 = pe.Node(interface = fsl.SliceTimer(), name = 'NodeName_31719d90')

#Wraps command **fslmaths**
NodeHash_4c877cd0 = pe.Node(interface = fsl.MeanImage(), name = 'NodeName_4c877cd0')
NodeHash_4c877cd0.inputs.dimension = 'T'

#Wraps command **bet**
NodeHash_3408b180 = pe.Node(interface = fsl.BET(), name = 'NodeName_3408b180')
NodeHash_3408b180.inputs.mask = True
NodeHash_3408b180.inputs.no_output = True
NodeHash_3408b180.inputs.frac = 0.3

#Wraps command **fslmaths**
NodeHash_38006770 = pe.Node(interface = fsl.ApplyMask(), name = 'NodeName_38006770')

#Wraps command **fslstats**
NodeHash_4f70af60 = pe.Node(interface = fsl.ImageStats(), name = 'NodeName_4f70af60')
NodeHash_4f70af60.inputs.op_string = '-p 98'

#Custom interface wrapping function Getpercentthresh
NodeHash_58b8d460 = pe.Node(interface = firstlevelhelpers.Getpercentthresh, name = 'NodeName_58b8d460')
NodeHash_58b8d460.inputs.percentage = 0.1

#Wraps command **fslmaths**
NodeHash_52cb1850 = pe.Node(interface = fsl.Threshold(), name = 'NodeName_52cb1850')

#Wraps command **fslmaths**
NodeHash_131d6540 = pe.Node(interface = fsl.MinImage(), name = 'NodeName_131d6540')
NodeHash_131d6540.inputs.dimension = 'T'
NodeHash_131d6540.inputs.args = '-bin'

#Wraps command **fslmaths**
NodeHash_1df6b50 = pe.Node(interface = fsl.ChangeDataType(), name = 'NodeName_1df6b50')
NodeHash_1df6b50.inputs.output_datatype = 'char'

#Wraps command **fslstats**
NodeHash_299a17c0 = pe.Node(interface = fsl.ImageStats(), name = 'NodeName_299a17c0')
NodeHash_299a17c0.inputs.op_string = '-p 50'

#Wraps command **fslmaths**
NodeHash_51be6db0 = pe.Node(interface = fsl.DilateImage(), name = 'NodeName_51be6db0')
NodeHash_51be6db0.inputs.operation = 'max'

#Wraps command **fslmaths**
NodeHash_3c062790 = pe.Node(interface = fsl.ApplyMask(), name = 'NodeName_3c062790')

#Wraps command **fslmaths**
NodeHash_5751d520 = pe.Node(interface = fsl.MeanImage(), name = 'NodeName_5751d520')

#Custom interface wrapping function Getpercentthresh
NodeHash_4820cc00 = pe.Node(interface = firstlevelhelpers.Getpercentthresh, name = 'NodeName_4820cc00')
NodeHash_4820cc00.inputs.percentage = 0.75

#Custom interface wrapping function Getinormscale
NodeHash_5c21bb50 = pe.Node(interface = firstlevelhelpers.Getinormscale, name = 'NodeName_5c21bb50')

#Custom interface wrapping function Tsv2subjectinfo
NodeHash_1c7f10d0 = pe.Node(interface = firstlevelhelpers.Tsv2subjectinfo, name = 'NodeName_1c7f10d0')

#Custom interface wrapping function Getusan
NodeHash_68d20430 = pe.Node(interface = firstlevelhelpers.Getusan, name = 'NodeName_68d20430')

#Wraps command **susan**
NodeHash_54ff40b0 = pe.Node(interface = fsl.SUSAN(), name = 'NodeName_54ff40b0')
NodeHash_54ff40b0.inputs.fwhm = 5
NodeHash_54ff40b0.inputs.dimension = 3
NodeHash_54ff40b0.inputs.use_median = 1

#Wraps command **fslmaths**
NodeHash_52ab58a0 = pe.Node(interface = fsl.ApplyMask(), name = 'NodeName_52ab58a0')

#Wraps command **fslmaths**
NodeHash_26b20d20 = pe.Node(interface = fsl.BinaryMaths(), name = 'NodeName_26b20d20')
NodeHash_26b20d20.inputs.operation = 'mul'

#Wraps command **fslmaths**
NodeHash_5dbd1810 = pe.Node(interface = fsl.MeanImage(), name = 'NodeName_5dbd1810')
NodeHash_5dbd1810.inputs.dimension = 'T'

#Wraps command **fslmaths**
NodeHash_3166e500 = pe.Node(interface = fsl.TemporalFilter(), name = 'NodeName_3166e500')
NodeHash_3166e500.inputs.highpass_sigma = 25

#Wraps command **fslmaths**
NodeHash_5fa85ed0 = pe.Node(interface = fsl.BinaryMaths(), name = 'NodeName_5fa85ed0')
NodeHash_5fa85ed0.inputs.operation = 'add'

#Wraps command **fslmaths**
NodeHash_5fa8ed90 = pe.Node(interface = fsl.MeanImage(), name = 'NodeName_5fa8ed90')
NodeHash_5fa8ed90.inputs.dimension = 'T'

#Makes a model specification compatible with spm/fsl designers.
NodeHash_1dc46c0 = pe.Node(interface = modelgen.SpecifyModel(), name = 'NodeName_1dc46c0')
NodeHash_1dc46c0.inputs.input_units = 'secs'
NodeHash_1dc46c0.inputs.high_pass_filter_cutoff = 0
NodeHash_1dc46c0.inputs.time_repetition = 2.0

#Wraps command **film_gls**
NodeHash_2908670 = pe.Node(interface = fsl.FILMGLS(), name = 'NodeName_2908670')
NodeHash_2908670.inputs.threshold = 1000

#Generate FEAT specific files
NodeHash_2563e620 = pe.Node(interface = fsl.Level1Design(), name = 'NodeName_2563e620')
NodeHash_2563e620.inputs.interscan_interval = 2.0
NodeHash_2563e620.inputs.bases = {'dgamma':{'derivs': False}}
NodeHash_2563e620.inputs.model_serial_correlations = True
NodeHash_2563e620.inputs.contrasts = [('con-incon', 'T', ['congruent_correct', 'congruent_correct'], [-1, 1])]

#Wraps command **feat_model**
NodeHash_84ccc60 = pe.Node(interface = fsl.FEATModel(), name = 'NodeName_84ccc60')

#Generic datasink module to store structured outputs
NodeHash_62c69f30 = pe.Node(interface = io.DataSink(), name = 'NodeName_62c69f30')
NodeHash_62c69f30.inputs.base_directory = '/tmp/FIRSTLEVEL'

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_68d20430, 'usan', NodeHash_54ff40b0, 'usans')
analysisflow.connect(NodeHash_4820cc00, 'value', NodeHash_68d20430, 'brightness_thresh')
analysisflow.connect(NodeHash_5751d520, 'out_file', NodeHash_68d20430, 'in_file')
analysisflow.connect(NodeHash_2cc3ef00, 'roi_file', NodeHash_31e5e3a0, 'in_file')
analysisflow.connect(NodeHash_643355b0, 'func', NodeHash_410f2c90, 'in_file')
analysisflow.connect(NodeHash_643355b0, 'func', NodeHash_2cc3ef00, 'in_file')
analysisflow.connect(NodeHash_643355b0, 'events', NodeHash_1c7f10d0, 'in_file')
analysisflow.connect(NodeHash_643355b0, 'anat', NodeHash_34338fc0, 'in_file')
analysisflow.connect(NodeHash_643355b0, 'anat', NodeHash_31e5e3a0, 'reference')
analysisflow.connect(NodeHash_643355b0, 'anat', NodeHash_2b027090, 'in_file')
analysisflow.connect(NodeHash_64138c50, 'sub_id', NodeHash_643355b0, 'sub_id')
analysisflow.connect(NodeHash_2908670, 'results_dir', NodeHash_62c69f30, 'firstlevel')
analysisflow.connect(NodeHash_5fa85ed0, 'out_file', NodeHash_2908670, 'in_file')
analysisflow.connect(NodeHash_84ccc60, 'design_file', NodeHash_2908670, 'design_file')
analysisflow.connect(NodeHash_84ccc60, 'con_file', NodeHash_2908670, 'tcon_file')
analysisflow.connect(NodeHash_2563e620, 'ev_files', NodeHash_84ccc60, 'ev_files')
analysisflow.connect(NodeHash_2563e620, 'fsf_files', NodeHash_84ccc60, 'fsf_file')
analysisflow.connect(NodeHash_1dc46c0, 'session_info', NodeHash_2563e620, 'session_info')
analysisflow.connect(NodeHash_5fa85ed0, 'out_file', NodeHash_1dc46c0, 'functional_runs')
analysisflow.connect(NodeHash_1c7f10d0, 'subject_info', NodeHash_1dc46c0, 'subject_info')
analysisflow.connect(NodeHash_5fa85ed0, 'out_file', NodeHash_5fa8ed90, 'in_file')
analysisflow.connect(NodeHash_5dbd1810, 'out_file', NodeHash_5fa85ed0, 'operand_file')
analysisflow.connect(NodeHash_3166e500, 'out_file', NodeHash_5fa85ed0, 'in_file')
analysisflow.connect(NodeHash_26b20d20, 'out_file', NodeHash_3166e500, 'in_file')
analysisflow.connect(NodeHash_26b20d20, 'out_file', NodeHash_5dbd1810, 'in_file')
analysisflow.connect(NodeHash_5c21bb50, 'value', NodeHash_26b20d20, 'operand_value')
analysisflow.connect(NodeHash_52ab58a0, 'out_file', NodeHash_26b20d20, 'in_file')
analysisflow.connect(NodeHash_299a17c0, 'out_stat', NodeHash_5c21bb50, 'medianval')
analysisflow.connect(NodeHash_51be6db0, 'out_file', NodeHash_52ab58a0, 'mask_file')
analysisflow.connect(NodeHash_54ff40b0, 'smoothed_file', NodeHash_52ab58a0, 'in_file')
analysisflow.connect(NodeHash_4820cc00, 'value', NodeHash_54ff40b0, 'brightness_threshold')
analysisflow.connect(NodeHash_299a17c0, 'out_stat', NodeHash_4820cc00, 'value')
analysisflow.connect(NodeHash_58b8d460, 'value', NodeHash_52cb1850, 'thresh')
analysisflow.connect(NodeHash_4f70af60, 'out_stat', NodeHash_58b8d460, 'value')
analysisflow.connect(NodeHash_3c062790, 'out_file', NodeHash_54ff40b0, 'in_file')
analysisflow.connect(NodeHash_3c062790, 'out_file', NodeHash_5751d520, 'in_file')
analysisflow.connect(NodeHash_51be6db0, 'out_file', NodeHash_3c062790, 'mask_file')
analysisflow.connect(NodeHash_410f2c90, 'out_file', NodeHash_3c062790, 'in_file')
analysisflow.connect(NodeHash_410f2c90, 'out_file', NodeHash_299a17c0, 'in_file')
analysisflow.connect(NodeHash_38006770, 'out_file', NodeHash_52cb1850, 'in_file')
analysisflow.connect(NodeHash_1df6b50, 'out_file', NodeHash_51be6db0, 'in_file')
analysisflow.connect(NodeHash_1df6b50, 'out_file', NodeHash_299a17c0, 'mask_file')
analysisflow.connect(NodeHash_131d6540, 'out_file', NodeHash_1df6b50, 'in_file')
analysisflow.connect(NodeHash_52cb1850, 'out_file', NodeHash_131d6540, 'in_file')
analysisflow.connect(NodeHash_38006770, 'out_file', NodeHash_4f70af60, 'in_file')
analysisflow.connect(NodeHash_410f2c90, 'out_file', NodeHash_38006770, 'in_file')
analysisflow.connect(NodeHash_3408b180, 'mask_file', NodeHash_38006770, 'mask_file')
analysisflow.connect(NodeHash_4c877cd0, 'out_file', NodeHash_3408b180, 'in_file')
analysisflow.connect(NodeHash_410f2c90, 'out_file', NodeHash_4c877cd0, 'in_file')
analysisflow.connect(NodeHash_410f2c90, 'par_file', NodeHash_3c666410, 'in_file')
analysisflow.connect(NodeHash_2cc3ef00, 'roi_file', NodeHash_379184b0, 'in_file')
analysisflow.connect(NodeHash_2cc3ef00, 'roi_file', NodeHash_410f2c90, 'ref_file')
analysisflow.connect(NodeHash_31e5e3a0, 'out_matrix_file', NodeHash_433f9c80, 'in_file')
analysisflow.connect(NodeHash_2db5da50, 'out_matrix_file', NodeHash_433f9c80, 'in_file2')
analysisflow.connect(NodeHash_30cfe660, 'MNI_mask', NodeHash_34338fc0, 'refmask_file')
analysisflow.connect(NodeHash_30cfe660, 'MNI_head', NodeHash_34338fc0, 'ref_file')
analysisflow.connect(NodeHash_30cfe660, 'MNI_brain', NodeHash_2db5da50, 'reference')
analysisflow.connect(NodeHash_2db5da50, 'out_matrix_file', NodeHash_34338fc0, 'affine_file')
analysisflow.connect(NodeHash_2b027090, 'out_file', NodeHash_2db5da50, 'in_file')
analysisflow.connect(NodeHash_379184b0, 'out_matrix_file', NodeHash_31e5e3a0, 'in_matrix_file')
analysisflow.connect(NodeHash_2b027090, 'out_file', NodeHash_379184b0, 'reference')
analysisflow.connect(NodeHash_30cfd500, 'out_file', NodeHash_31e5e3a0, 'wm_seg')
analysisflow.connect(NodeHash_31fd8990, 'out', NodeHash_30cfd500, 'in_file')
analysisflow.connect(NodeHash_27d1f090, 'partial_volume_files', NodeHash_31fd8990, 'inlist')
analysisflow.connect(NodeHash_2b027090, 'out_file', NodeHash_27d1f090, 'in_files')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 1} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
