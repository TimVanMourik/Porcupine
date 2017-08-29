#This is a Nipype generator. Warning, here be dragons.
import sys
import nipype
import nipype.pipeline as pe
import nipype.interfaces.utility as utility
import nipype.interfaces.io as io
import nipype.interfaces.fsl as fsl
sys.path.append('/media/lukas/goliath/Porcupine/example_workflows/FEAT_fsl_complete_firstlevel_and_secondlevel')
import firstlevelhelpers
import nipype.algorithms.modelgen as modelgen

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Basic interface class generates identity mappings
NodeHash_36e8e10 = pe.Node(utility.IdentityInterface(fields=['sub_id']), name = 'NodeName_36e8e10')
NodeHash_36e8e10.inputs.sub_id = ['sub-02', 'sub-03', 'sub-04', 'sub-05', 'sub-06', 'sub-07', 'sub-08', 'sub-09', 'sub-10', 'sub-11', 'sub-12', 'sub-13', 'sub-14', 'sub-15', 'sub-16', 'sub-17', 'sub-18', 'sub-19', 'sub-20', 'sub-21']

#Flexibly collect data from disk to feed into workflows.
NodeHash_2590a60 = pe.MapNode(io.SelectFiles(templates={'anat':'{sub_id}/anat/{sub_id}_T1w.nii.gz','events':'{sub_id}/func/{sub_id}_task-simon_run-1_events.tsv','func':'{sub_id}/func/{sub_id}_task-simon_run-1_bold.nii.gz'}), name = 'NodeName_2590a60', iterfield = ['sub_id'])
NodeHash_2590a60.inputs.base_directory = '/media/lukas/goliath/Porcupine/example_workflows/example_data'
NodeHash_2590a60.inputs.sort_filelist = True

#Generic datagrabber module that wraps around glob in an
NodeHash_3571f10 = pe.Node(io.S3DataGrabber(outfields=['outfiles']), name = 'NodeName_3571f10')
NodeHash_3571f10.inputs.anon = True
NodeHash_3571f10.inputs.bucket = 'openneuro'
NodeHash_3571f10.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_3571f10.inputs.local_directory = '/tmp'
NodeHash_3571f10.inputs.sort_filelist = True
NodeHash_3571f10.inputs.template = 'sub-01/func/sub-01_task-simon_run-1_bold.nii.gz'

#Generic datagrabber module that wraps around glob in an
NodeHash_43ef2b0 = pe.Node(io.S3DataGrabber(outfields=['outfiles']), name = 'NodeName_43ef2b0')
NodeHash_43ef2b0.inputs.anon = True
NodeHash_43ef2b0.inputs.bucket = 'openneuro'
NodeHash_43ef2b0.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_43ef2b0.inputs.local_directory = '/tmp'
NodeHash_43ef2b0.inputs.sort_filelist = True
NodeHash_43ef2b0.inputs.template = 'sub-01/anat/sub-01_T1w.nii.gz'

#Generic datagrabber module that wraps around glob in an
NodeHash_442d600 = pe.Node(io.S3DataGrabber(outfields=['events']), name = 'NodeName_442d600')
NodeHash_442d600.inputs.anon = True
NodeHash_442d600.inputs.bucket = 'openneuro'
NodeHash_442d600.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_442d600.inputs.local_directory = '/tmp'
NodeHash_442d600.inputs.sort_filelist = True
NodeHash_442d600.inputs.template = 'sub-01/func/sub-01_task-simon_run-1_events.tsv'

#Basic interface class generates identity mappings
NodeHash_58c74a0 = pe.Node(utility.IdentityInterface(fields=['MNI_brain','MNI_head','MNI_mask']), name = 'NodeName_58c74a0')
NodeHash_58c74a0.inputs.MNI_brain = '/usr/share/fsl/5.0/data/standard/MNI152_T1_2mm_brain.nii.gz'
NodeHash_58c74a0.inputs.MNI_head = '/usr/share/fsl/5.0/data/standard/MNI152_T1_2mm.nii.gz'
NodeHash_58c74a0.inputs.MNI_mask = '/usr/share/fsl/5.0/data/standard/MNI152_T1_2mm_brain_mask_dil.nii.gz'

#Wraps command **bet**
NodeHash_622a1f0 = pe.MapNode(interface = fsl.BET(), name = 'NodeName_622a1f0', iterfield = ['in_file'])
NodeHash_622a1f0.inputs.frac = 0.3
NodeHash_622a1f0.inputs.robust = True

#Wraps command **fast**
NodeHash_67f9080 = pe.MapNode(interface = fsl.FAST(), name = 'NodeName_67f9080', iterfield = ['in_files'])

#Basic interface class to select specific elements from a list
NodeHash_85b99e0 = pe.MapNode(interface = utility.Select(), name = 'NodeName_85b99e0', iterfield = ['inlist'])
NodeHash_85b99e0.inputs.index = 2

#Wraps command **fslmaths**
NodeHash_87127f0 = pe.MapNode(interface = fsl.Threshold(), name = 'NodeName_87127f0', iterfield = ['in_file'])
NodeHash_87127f0.inputs.args = '-bin'
NodeHash_87127f0.inputs.thresh = 0.5

#Wraps command **flirt**
NodeHash_a717470 = pe.MapNode(interface = fsl.FLIRT(), name = 'NodeName_a717470', iterfield = ['in_file'])
NodeHash_a717470.inputs.cost = 'corratio'
NodeHash_a717470.inputs.dof = 12
NodeHash_a717470.inputs.no_resample = True
NodeHash_a717470.inputs.searchr_x = [-90, 90]
NodeHash_a717470.inputs.searchr_y = [-90, 90]
NodeHash_a717470.inputs.searchr_z = [-90, 90]

#Wraps command **fnirt**
NodeHash_e5fda50 = pe.MapNode(interface = fsl.FNIRT(), name = 'NodeName_e5fda50', iterfield = ['affine_file', 'in_file'])
NodeHash_e5fda50.inputs.config_file = 'T1_2_MNI152_2mm'
NodeHash_e5fda50.inputs.warp_resolution = (10, 10, 10)
NodeHash_e5fda50.inputs.field_file = True

#Wraps command **fslroi**
NodeHash_c0aecc0 = pe.MapNode(interface = fsl.ExtractROI(), name = 'NodeName_c0aecc0', iterfield = ['in_file'])
NodeHash_c0aecc0.inputs.t_min = 1
NodeHash_c0aecc0.inputs.t_size = 1

#Wraps command **flirt**
NodeHash_116bc560 = pe.MapNode(interface = fsl.FLIRT(), name = 'NodeName_116bc560', iterfield = ['in_file', 'reference'])

#Wraps command **flirt**
NodeHash_12fdde80 = pe.MapNode(interface = fsl.FLIRT(), name = 'NodeName_12fdde80', iterfield = ['in_file', 'in_matrix_file', 'reference', 'wm_seg'])
NodeHash_12fdde80.inputs.cost = 'bbr'
NodeHash_12fdde80.inputs.dof = 6
NodeHash_12fdde80.inputs.no_resample = True

#Wraps command **convert_xfm**
NodeHash_15c985f0 = pe.MapNode(interface = fsl.ConvertXFM(), name = 'NodeName_15c985f0', iterfield = ['in_file', 'in_file2'])
NodeHash_15c985f0.inputs.concat_xfm = True

#Wraps command **mcflirt**
NodeHash_192e67b0 = pe.MapNode(interface = fsl.MCFLIRT(), name = 'NodeName_192e67b0', iterfield = ['in_file', 'ref_file'])
NodeHash_192e67b0.inputs.interpolation = 'spline'
NodeHash_192e67b0.inputs.save_mats = True
NodeHash_192e67b0.inputs.save_plots = True
NodeHash_192e67b0.inputs.save_rms = True

#Wraps command **fsl_tsplot**
NodeHash_197c7b70 = pe.MapNode(interface = fsl.PlotMotionParams(), name = 'NodeName_197c7b70', iterfield = ['in_file'])
NodeHash_197c7b70.inputs.args = '-a x,y,z -w 640 -h 144'
NodeHash_197c7b70.inputs.in_source = 'fsl'
NodeHash_197c7b70.iterables = [('plot_type', ['rotations', 'translations'])]

#Wraps command **fslmaths**
NodeHash_19b48ea0 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_19b48ea0', iterfield = ['in_file'])
NodeHash_19b48ea0.inputs.dimension = 'T'

#Wraps command **bet**
NodeHash_1cd74c10 = pe.MapNode(interface = fsl.BET(), name = 'NodeName_1cd74c10', iterfield = ['in_file'])
NodeHash_1cd74c10.inputs.frac = 0.3
NodeHash_1cd74c10.inputs.mask = True
NodeHash_1cd74c10.inputs.no_output = True

#Wraps command **fslmaths**
NodeHash_1d9b36e0 = pe.MapNode(interface = fsl.ApplyMask(), name = 'NodeName_1d9b36e0', iterfield = ['in_file', 'mask_file'])

#Wraps command **fslstats**
NodeHash_1e61fc40 = pe.MapNode(interface = fsl.ImageStats(), name = 'NodeName_1e61fc40', iterfield = ['in_file'])
NodeHash_1e61fc40.inputs.op_string = '-p 98'

#Custom interface wrapping function Tsv2subjectinfo
NodeHash_2de62010 = pe.MapNode(interface = firstlevelhelpers.Tsv2subjectinfo, name = 'NodeName_2de62010', iterfield = ['in_file'])

#Custom interface wrapping function Getpercentthresh
NodeHash_371b270 = pe.MapNode(interface = firstlevelhelpers.Getpercentthresh, name = 'NodeName_371b270', iterfield = ['value'])
NodeHash_371b270.inputs.percentage = 0.75

#Custom interface wrapping function Getpercentthresh
NodeHash_22c5b530 = pe.MapNode(interface = firstlevelhelpers.Getpercentthresh, name = 'NodeName_22c5b530', iterfield = ['value'])
NodeHash_22c5b530.inputs.percentage = 0.1

#Wraps command **fslmaths**
NodeHash_1da3c7c0 = pe.MapNode(interface = fsl.Threshold(), name = 'NodeName_1da3c7c0', iterfield = ['in_file', 'thresh'])

#Wraps command **fslmaths**
NodeHash_2043ebe0 = pe.MapNode(interface = fsl.MinImage(), name = 'NodeName_2043ebe0', iterfield = ['in_file'])
NodeHash_2043ebe0.inputs.args = '-bin'
NodeHash_2043ebe0.inputs.dimension = 'T'

#Wraps command **fslmaths**
NodeHash_21822c10 = pe.MapNode(interface = fsl.ChangeDataType(), name = 'NodeName_21822c10', iterfield = ['in_file'])
NodeHash_21822c10.inputs.output_datatype = 'char'

#Wraps command **fslmaths**
NodeHash_222d93b0 = pe.MapNode(interface = fsl.DilateImage(), name = 'NodeName_222d93b0', iterfield = ['in_file'])
NodeHash_222d93b0.inputs.operation = 'max'

#Wraps command **fslstats**
NodeHash_22c7caf0 = pe.MapNode(interface = fsl.ImageStats(), name = 'NodeName_22c7caf0', iterfield = ['in_file', 'mask_file'])
NodeHash_22c7caf0.inputs.op_string = '-p 50'

#Wraps command **fslmaths**
NodeHash_24da4580 = pe.MapNode(interface = fsl.ApplyMask(), name = 'NodeName_24da4580', iterfield = ['in_file', 'mask_file'])

#Wraps command **fslmaths**
NodeHash_2e71b540 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_2e71b540', iterfield = ['in_file'])

#Custom interface wrapping function Getusan
NodeHash_2e104190 = pe.MapNode(interface = firstlevelhelpers.Getusan, name = 'NodeName_2e104190', iterfield = ['in_file', 'brightness_thresh'])

#Wraps command **susan**
NodeHash_2bee9d10 = pe.MapNode(interface = fsl.SUSAN(), name = 'NodeName_2bee9d10', iterfield = ['brightness_threshold', 'in_file', 'usans'])
NodeHash_2bee9d10.inputs.dimension = 3
NodeHash_2bee9d10.inputs.fwhm = 5
NodeHash_2bee9d10.inputs.use_median = 1

#Wraps command **fslmaths**
NodeHash_22d38f50 = pe.MapNode(interface = fsl.ApplyMask(), name = 'NodeName_22d38f50', iterfield = ['in_file', 'mask_file'])

#Custom interface wrapping function Getinormscale
NodeHash_3076fd0 = pe.MapNode(interface = firstlevelhelpers.Getinormscale, name = 'NodeName_3076fd0', iterfield = ['medianval'])

#Wraps command **fslmaths**
NodeHash_24c55180 = pe.MapNode(interface = fsl.BinaryMaths(), name = 'NodeName_24c55180', iterfield = ['in_file', 'operand_value'])
NodeHash_24c55180.inputs.operation = 'mul'

#Wraps command **fslmaths**
NodeHash_2652cec0 = pe.MapNode(interface = fsl.TemporalFilter(), name = 'NodeName_2652cec0', iterfield = ['in_file'])
NodeHash_2652cec0.inputs.highpass_sigma = 25

#Wraps command **fslmaths**
NodeHash_25a6b0a0 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_25a6b0a0', iterfield = ['in_file'])
NodeHash_25a6b0a0.inputs.dimension = 'T'

#Wraps command **fslmaths**
NodeHash_2751f320 = pe.MapNode(interface = fsl.BinaryMaths(), name = 'NodeName_2751f320', iterfield = ['in_file', 'operand_file'])
NodeHash_2751f320.inputs.operation = 'add'

#Makes a model specification compatible with spm/fsl designers.
NodeHash_28baada0 = pe.MapNode(interface = modelgen.SpecifyModel(), name = 'NodeName_28baada0', iterfield = ['functional_runs', 'subject_info'])
NodeHash_28baada0.inputs.high_pass_filter_cutoff = 0
NodeHash_28baada0.inputs.input_units = 'secs'
NodeHash_28baada0.inputs.time_repetition = 2.0

#Generate FEAT specific files
NodeHash_2c11b030 = pe.MapNode(interface = fsl.Level1Design(), name = 'NodeName_2c11b030', iterfield = ['session_info'])
NodeHash_2c11b030.inputs.bases = {'dgamma':{'derivs': False}}
NodeHash_2c11b030.inputs.contrasts = [('con-incon', 'T', ['congruent_correct', 'congruent_correct'], [-1, 1])]
NodeHash_2c11b030.inputs.interscan_interval = 2.0
NodeHash_2c11b030.inputs.model_serial_correlations = True

#Wraps command **feat_model**
NodeHash_2c01aab0 = pe.MapNode(interface = fsl.FEATModel(), name = 'NodeName_2c01aab0', iterfield = ['ev_files', 'fsf_file'])

#Wraps command **film_gls**
NodeHash_27a03500 = pe.MapNode(interface = fsl.FILMGLS(), name = 'NodeName_27a03500', iterfield = ['design_file', 'in_file', 'tcon_file'])

#Wraps command **fslmaths**
NodeHash_28c9f610 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_28c9f610', iterfield = ['in_file'])
NodeHash_28c9f610.inputs.dimension = 'T'

#Generic datasink module to store structured outputs
NodeHash_2a4b8540 = pe.Node(interface = io.DataSink(), name = 'NodeName_2a4b8540')
NodeHash_2a4b8540.inputs.base_directory = '/tmp/FIRSTLEVEL'

#Basic interface class to select specific elements from a list
NodeHash_23687a90 = pe.MapNode(interface = utility.Select(), name = 'NodeName_23687a90', iterfield = ['inlist'])
NodeHash_23687a90.inputs.index = 0

#Basic interface class to select specific elements from a list
NodeHash_31d6aa0 = pe.MapNode(interface = utility.Select(), name = 'NodeName_31d6aa0', iterfield = ['inlist'])
NodeHash_31d6aa0.inputs.index = 0

#Wraps command **applywarp**
NodeHash_2a4718a0 = pe.MapNode(interface = fsl.ApplyWarp(), name = 'NodeName_2a4718a0', iterfield = ['in_file', 'field_file', 'premat'])
NodeHash_2a4718a0.inputs.interp = 'trilinear'

#Wraps command **applywarp**
NodeHash_2fa5d960 = pe.MapNode(interface = fsl.ApplyWarp(), name = 'NodeName_2fa5d960', iterfield = ['in_file', 'field_file', 'premat'])
NodeHash_2fa5d960.inputs.interp = 'trilinear'

#Wraps command **fslmerge**
NodeHash_1d9e5dc0 = pe.Node(interface = fsl.Merge(), name = 'NodeName_1d9e5dc0')
NodeHash_1d9e5dc0.inputs.dimension = 't'

#Wraps command **fslmerge**
NodeHash_23af6d10 = pe.Node(interface = fsl.Merge(), name = 'NodeName_23af6d10')
NodeHash_23af6d10.inputs.dimension = 't'

#Generate subject specific second level model
NodeHash_420aa140 = pe.Node(interface = fsl.L2Model(), name = 'NodeName_420aa140')
NodeHash_420aa140.inputs.num_copes = 21

#Wraps command **flameo**
NodeHash_4239cdb0 = pe.Node(interface = fsl.FLAMEO(), name = 'NodeName_4239cdb0')
NodeHash_4239cdb0.inputs.run_mode = 'flame1'

#Wraps command **smoothest**
NodeHash_28c1ae60 = pe.Node(interface = fsl.SmoothEstimate(), name = 'NodeName_28c1ae60')

#Wraps command **cluster**
NodeHash_4576d910 = pe.Node(interface = fsl.Cluster(), name = 'NodeName_4576d910')
NodeHash_4576d910.inputs.threshold = 2.3
NodeHash_4576d910.inputs.pthreshold = 0.05

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_e5fda50, 'field_file', NodeHash_2a4718a0, 'field_file')
analysisflow.connect(NodeHash_e5fda50, 'field_file', NodeHash_2fa5d960, 'field_file')
analysisflow.connect(NodeHash_28c1ae60, 'volume', NodeHash_4576d910, 'volume')
analysisflow.connect(NodeHash_28c1ae60, 'dlh', NodeHash_4576d910, 'dlh')
analysisflow.connect(NodeHash_1d9e5dc0, 'merged_file', NodeHash_4576d910, 'cope_file')
analysisflow.connect(NodeHash_4239cdb0, 'zstats', NodeHash_4576d910, 'in_file')
analysisflow.connect(NodeHash_420aa140, 'design_con', NodeHash_4239cdb0, 't_con_file')
analysisflow.connect(NodeHash_420aa140, 'design_grp', NodeHash_4239cdb0, 'cov_split_file')
analysisflow.connect(NodeHash_420aa140, 'design_mat', NodeHash_4239cdb0, 'design_file')
analysisflow.connect(NodeHash_4239cdb0, 'res4d', NodeHash_28c1ae60, 'residual_fit_file')
analysisflow.connect(NodeHash_58c74a0, 'MNI_mask', NodeHash_28c1ae60, 'mask_file')
analysisflow.connect(NodeHash_4239cdb0, 'tdof', NodeHash_28c1ae60, 'dof')
analysisflow.connect(NodeHash_23af6d10, 'merged_file', NodeHash_4239cdb0, 'var_cope_file')
analysisflow.connect(NodeHash_31d6aa0, 'out', NodeHash_2fa5d960, 'in_file')
analysisflow.connect(NodeHash_58c74a0, 'MNI_mask', NodeHash_4239cdb0, 'mask_file')
analysisflow.connect(NodeHash_1d9e5dc0, 'merged_file', NodeHash_4239cdb0, 'cope_file')
analysisflow.connect(NodeHash_2fa5d960, 'out_file', NodeHash_23af6d10, 'in_files')
analysisflow.connect(NodeHash_2a4718a0, 'out_file', NodeHash_1d9e5dc0, 'in_files')
analysisflow.connect(NodeHash_15c985f0, 'out_file', NodeHash_2fa5d960, 'premat')
analysisflow.connect(NodeHash_15c985f0, 'out_file', NodeHash_2a4718a0, 'premat')
analysisflow.connect(NodeHash_23687a90, 'out', NodeHash_2a4718a0, 'in_file')
analysisflow.connect(NodeHash_58c74a0, 'MNI_brain', NodeHash_2fa5d960, 'ref_file')
analysisflow.connect(NodeHash_58c74a0, 'MNI_brain', NodeHash_2a4718a0, 'ref_file')
analysisflow.connect(NodeHash_27a03500, 'copes', NodeHash_23687a90, 'inlist')
analysisflow.connect(NodeHash_27a03500, 'varcopes', NodeHash_31d6aa0, 'inlist')
analysisflow.connect(NodeHash_1e61fc40, 'out_stat', NodeHash_371b270, 'value')
analysisflow.connect(NodeHash_3076fd0, 'value', NodeHash_24c55180, 'operand_value')
analysisflow.connect(NodeHash_2e71b540, 'out_file', NodeHash_2e104190, 'in_file')
analysisflow.connect(NodeHash_1e61fc40, 'out_stat', NodeHash_22c5b530, 'value')
analysisflow.connect(NodeHash_22c5b530, 'out_val', NodeHash_1da3c7c0, 'thresh')
analysisflow.connect(NodeHash_2e104190, 'usan', NodeHash_2bee9d10, 'usans')
analysisflow.connect(NodeHash_371b270, 'out_val', NodeHash_2e104190, 'brightness_thresh')
analysisflow.connect(NodeHash_371b270, 'out_val', NodeHash_2bee9d10, 'brightness_threshold')
analysisflow.connect(NodeHash_22c7caf0, 'out_stat', NodeHash_3076fd0, 'medianval')
analysisflow.connect(NodeHash_2de62010, 'subject_info', NodeHash_28baada0, 'subject_info')
analysisflow.connect(NodeHash_2590a60, 'events', NodeHash_2de62010, 'in_file')
analysisflow.connect(NodeHash_622a1f0, 'out_file', NodeHash_67f9080, 'in_files')
analysisflow.connect(NodeHash_67f9080, 'partial_volume_files', NodeHash_85b99e0, 'inlist')
analysisflow.connect(NodeHash_85b99e0, 'out', NodeHash_87127f0, 'in_file')
analysisflow.connect(NodeHash_87127f0, 'out_file', NodeHash_12fdde80, 'wm_seg')
analysisflow.connect(NodeHash_622a1f0, 'out_file', NodeHash_116bc560, 'reference')
analysisflow.connect(NodeHash_116bc560, 'out_matrix_file', NodeHash_12fdde80, 'in_matrix_file')
analysisflow.connect(NodeHash_622a1f0, 'out_file', NodeHash_a717470, 'in_file')
analysisflow.connect(NodeHash_a717470, 'out_matrix_file', NodeHash_e5fda50, 'affine_file')
analysisflow.connect(NodeHash_58c74a0, 'MNI_brain', NodeHash_a717470, 'reference')
analysisflow.connect(NodeHash_58c74a0, 'MNI_head', NodeHash_e5fda50, 'ref_file')
analysisflow.connect(NodeHash_58c74a0, 'MNI_mask', NodeHash_e5fda50, 'refmask_file')
analysisflow.connect(NodeHash_a717470, 'out_matrix_file', NodeHash_15c985f0, 'in_file2')
analysisflow.connect(NodeHash_12fdde80, 'out_matrix_file', NodeHash_15c985f0, 'in_file')
analysisflow.connect(NodeHash_c0aecc0, 'roi_file', NodeHash_192e67b0, 'ref_file')
analysisflow.connect(NodeHash_c0aecc0, 'roi_file', NodeHash_116bc560, 'in_file')
analysisflow.connect(NodeHash_192e67b0, 'par_file', NodeHash_197c7b70, 'in_file')
analysisflow.connect(NodeHash_192e67b0, 'out_file', NodeHash_19b48ea0, 'in_file')
analysisflow.connect(NodeHash_19b48ea0, 'out_file', NodeHash_1cd74c10, 'in_file')
analysisflow.connect(NodeHash_1cd74c10, 'mask_file', NodeHash_1d9b36e0, 'mask_file')
analysisflow.connect(NodeHash_192e67b0, 'out_file', NodeHash_1d9b36e0, 'in_file')
analysisflow.connect(NodeHash_1d9b36e0, 'out_file', NodeHash_1e61fc40, 'in_file')
analysisflow.connect(NodeHash_1da3c7c0, 'out_file', NodeHash_2043ebe0, 'in_file')
analysisflow.connect(NodeHash_2043ebe0, 'out_file', NodeHash_21822c10, 'in_file')
analysisflow.connect(NodeHash_21822c10, 'out_file', NodeHash_22c7caf0, 'mask_file')
analysisflow.connect(NodeHash_21822c10, 'out_file', NodeHash_222d93b0, 'in_file')
analysisflow.connect(NodeHash_1d9b36e0, 'out_file', NodeHash_1da3c7c0, 'in_file')
analysisflow.connect(NodeHash_192e67b0, 'out_file', NodeHash_22c7caf0, 'in_file')
analysisflow.connect(NodeHash_192e67b0, 'out_file', NodeHash_24da4580, 'in_file')
analysisflow.connect(NodeHash_222d93b0, 'out_file', NodeHash_24da4580, 'mask_file')
analysisflow.connect(NodeHash_24da4580, 'out_file', NodeHash_2e71b540, 'in_file')
analysisflow.connect(NodeHash_24da4580, 'out_file', NodeHash_2bee9d10, 'in_file')
analysisflow.connect(NodeHash_2bee9d10, 'smoothed_file', NodeHash_22d38f50, 'in_file')
analysisflow.connect(NodeHash_222d93b0, 'out_file', NodeHash_22d38f50, 'mask_file')
analysisflow.connect(NodeHash_22d38f50, 'out_file', NodeHash_24c55180, 'in_file')
analysisflow.connect(NodeHash_24c55180, 'out_file', NodeHash_25a6b0a0, 'in_file')
analysisflow.connect(NodeHash_24c55180, 'out_file', NodeHash_2652cec0, 'in_file')
analysisflow.connect(NodeHash_2652cec0, 'out_file', NodeHash_2751f320, 'in_file')
analysisflow.connect(NodeHash_25a6b0a0, 'out_file', NodeHash_2751f320, 'operand_file')
analysisflow.connect(NodeHash_2751f320, 'out_file', NodeHash_28c9f610, 'in_file')
analysisflow.connect(NodeHash_2751f320, 'out_file', NodeHash_28baada0, 'functional_runs')
analysisflow.connect(NodeHash_28baada0, 'session_info', NodeHash_2c11b030, 'session_info')
analysisflow.connect(NodeHash_2c11b030, 'fsf_files', NodeHash_2c01aab0, 'fsf_file')
analysisflow.connect(NodeHash_2c11b030, 'ev_files', NodeHash_2c01aab0, 'ev_files')
analysisflow.connect(NodeHash_2c01aab0, 'con_file', NodeHash_27a03500, 'tcon_file')
analysisflow.connect(NodeHash_2c01aab0, 'design_file', NodeHash_27a03500, 'design_file')
analysisflow.connect(NodeHash_2751f320, 'out_file', NodeHash_27a03500, 'in_file')
analysisflow.connect(NodeHash_27a03500, 'results_dir', NodeHash_2a4b8540, 'firstlevel')
analysisflow.connect(NodeHash_36e8e10, 'sub_id', NodeHash_2590a60, 'sub_id')
analysisflow.connect(NodeHash_2590a60, 'anat', NodeHash_622a1f0, 'in_file')
analysisflow.connect(NodeHash_2590a60, 'anat', NodeHash_12fdde80, 'reference')
analysisflow.connect(NodeHash_2590a60, 'anat', NodeHash_e5fda50, 'in_file')
analysisflow.connect(NodeHash_2590a60, 'func', NodeHash_c0aecc0, 'in_file')
analysisflow.connect(NodeHash_2590a60, 'func', NodeHash_192e67b0, 'in_file')
analysisflow.connect(NodeHash_c0aecc0, 'roi_file', NodeHash_12fdde80, 'in_file')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 10} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.base_dir = '/media/lukas/goliath/Porcupine/example_workflows/FEAT_fsl_complete_firstlevel_and_secondlevel'
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
