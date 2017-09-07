#This is a Nipype generator. Warning, here be dragons.
import sys
import nipype
import nipype.pipeline as pe
import nipype.interfaces.utility as utility
import nipype.interfaces.io as io
import nipype.interfaces.fsl as fsl
import firstlevelhelpers
import nipype.algorithms.modelgen as modelgen

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Basic interface class generates identity mappings
NodeHash_1a6ef50 = pe.Node(utility.IdentityInterface(fields=['sub_id']), name = 'NodeName_1a6ef50')
NodeHash_1a6ef50.inputs.sub_id = ['sub-02', 'sub-03', 'sub-04', 'sub-05', 'sub-06', 'sub-07', 'sub-08', 'sub-09', 'sub-10', 'sub-11', 'sub-12', 'sub-13', 'sub-14', 'sub-15', 'sub-16', 'sub-17', 'sub-18', 'sub-19', 'sub-20', 'sub-21']

#Generic datagrabber module that wraps around glob in an
NodeHash_1ad6ca0 = pe.MapNode(io.S3DataGrabber(infields=['field_template','sub_id'], outfields=['func','events','anat']), name = 'NodeName_1ad6ca0', iterfield = ['sub_id'])
NodeHash_1ad6ca0.inputs.anon = True
NodeHash_1ad6ca0.inputs.bucket = 'openneuro'
NodeHash_1ad6ca0.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_1ad6ca0.inputs.local_directory = '/tmp'
NodeHash_1ad6ca0.inputs.sort_filelist = True
NodeHash_1ad6ca0.inputs.template = '*'
NodeHash_1ad6ca0.inputs.template_args = dict(func=[['sub_id', 'sub_id']], events=[['sub_id', 'sub_id']], anat=[['sub_id', 'sub_id']])
NodeHash_1ad6ca0.inputs.field_template = dict(func='%s/func/%s_task-simon_run-1_bold.nii.gz', events='%s/func/%s_task-simon_run-1_events.tsv', anat='%s/anat/%s_T1w.nii.gz')

#Wraps command **bet**
NodeHash_2062490 = pe.MapNode(interface = fsl.BET(), name = 'NodeName_2062490', iterfield = ['in_file'])
NodeHash_2062490.inputs.frac = 0.3
NodeHash_2062490.inputs.robust = True

#Wraps command **fast**
NodeHash_2e9d1d0 = pe.MapNode(interface = fsl.FAST(), name = 'NodeName_2e9d1d0', iterfield = ['in_files'])

#Basic interface class to select specific elements from a list
NodeHash_4ce0570 = pe.MapNode(interface = utility.Select(), name = 'NodeName_4ce0570', iterfield = ['inlist'])
NodeHash_4ce0570.inputs.index = 2

#Wraps command **fslmaths**
NodeHash_58c9230 = pe.MapNode(interface = fsl.Threshold(), name = 'NodeName_58c9230', iterfield = ['in_file'])
NodeHash_58c9230.inputs.args = '-bin'
NodeHash_58c9230.inputs.thresh = 0.5

#Wraps command **fslroi**
NodeHash_4d25ff0 = pe.MapNode(interface = fsl.ExtractROI(), name = 'NodeName_4d25ff0', iterfield = ['in_file'])
NodeHash_4d25ff0.inputs.t_min = 1
NodeHash_4d25ff0.inputs.t_size = 1

#Wraps command **flirt**
NodeHash_79b5240 = pe.MapNode(interface = fsl.FLIRT(), name = 'NodeName_79b5240', iterfield = ['in_file', 'reference'])

#Wraps command **flirt**
NodeHash_8f61130 = pe.MapNode(interface = fsl.FLIRT(), name = 'NodeName_8f61130', iterfield = ['in_file', 'in_matrix_file', 'reference', 'wm_seg'])
NodeHash_8f61130.inputs.cost = 'bbr'
NodeHash_8f61130.inputs.dof = 6
NodeHash_8f61130.inputs.no_resample = True

#Wraps command **mcflirt**
NodeHash_c3ef3c0 = pe.MapNode(interface = fsl.MCFLIRT(), name = 'NodeName_c3ef3c0', iterfield = ['in_file', 'ref_file'])
NodeHash_c3ef3c0.inputs.interpolation = 'spline'
NodeHash_c3ef3c0.inputs.save_mats = True
NodeHash_c3ef3c0.inputs.save_plots = True
NodeHash_c3ef3c0.inputs.save_rms = True

#Wraps command **fsl_tsplot**
NodeHash_c4a9c30 = pe.MapNode(interface = fsl.PlotMotionParams(), name = 'NodeName_c4a9c30', iterfield = ['in_file'])
NodeHash_c4a9c30.inputs.args = '-a x,y,z -w 640 -h 144'
NodeHash_c4a9c30.inputs.in_source = 'fsl'
NodeHash_c4a9c30.iterables = [('plot_type', ['rotations', 'translations'])]

#Wraps command **fslmaths**
NodeHash_1040c610 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_1040c610', iterfield = ['in_file'])
NodeHash_1040c610.inputs.dimension = 'T'

#Wraps command **bet**
NodeHash_1212d0d0 = pe.MapNode(interface = fsl.BET(), name = 'NodeName_1212d0d0', iterfield = ['in_file'])
NodeHash_1212d0d0.inputs.frac = 0.3
NodeHash_1212d0d0.inputs.mask = True
NodeHash_1212d0d0.inputs.no_output = True

#Wraps command **fslmaths**
NodeHash_1274e060 = pe.MapNode(interface = fsl.ApplyMask(), name = 'NodeName_1274e060', iterfield = ['in_file', 'mask_file'])

#Wraps command **fslstats**
NodeHash_149ec020 = pe.MapNode(interface = fsl.ImageStats(), name = 'NodeName_149ec020', iterfield = ['in_file'])
NodeHash_149ec020.inputs.op_string = '-p 98'

#Custom interface wrapping function Tsv2subjectinfo
NodeHash_127d16f0 = pe.MapNode(interface = firstlevelhelpers.Tsv2subjectinfo, name = 'NodeName_127d16f0', iterfield = ['in_file'])

#Custom interface wrapping function Getpercentthresh
NodeHash_14e113c0 = pe.MapNode(interface = firstlevelhelpers.Getpercentthresh, name = 'NodeName_14e113c0', iterfield = ['value'])
NodeHash_14e113c0.inputs.percentage = 0.75

#Custom interface wrapping function Getpercentthresh
NodeHash_14e3d7c0 = pe.MapNode(interface = firstlevelhelpers.Getpercentthresh, name = 'NodeName_14e3d7c0', iterfield = ['value'])
NodeHash_14e3d7c0.inputs.percentage = 0.1

#Wraps command **fslmaths**
NodeHash_157bd2b0 = pe.MapNode(interface = fsl.Threshold(), name = 'NodeName_157bd2b0', iterfield = ['in_file', 'thresh'])

#Wraps command **fslmaths**
NodeHash_15f74220 = pe.MapNode(interface = fsl.MinImage(), name = 'NodeName_15f74220', iterfield = ['in_file'])
NodeHash_15f74220.inputs.args = '-bin'
NodeHash_15f74220.inputs.dimension = 'T'

#Wraps command **fslmaths**
NodeHash_16d421a0 = pe.MapNode(interface = fsl.ChangeDataType(), name = 'NodeName_16d421a0', iterfield = ['in_file'])
NodeHash_16d421a0.inputs.output_datatype = 'char'

#Wraps command **fslmaths**
NodeHash_1801caa0 = pe.MapNode(interface = fsl.DilateImage(), name = 'NodeName_1801caa0', iterfield = ['in_file'])
NodeHash_1801caa0.inputs.operation = 'max'

#Wraps command **fslstats**
NodeHash_18508680 = pe.MapNode(interface = fsl.ImageStats(), name = 'NodeName_18508680', iterfield = ['in_file', 'mask_file'])
NodeHash_18508680.inputs.op_string = '-p 50'

#Wraps command **fslmaths**
NodeHash_181e69e0 = pe.MapNode(interface = fsl.ApplyMask(), name = 'NodeName_181e69e0', iterfield = ['in_file', 'mask_file'])

#Wraps command **fslmaths**
NodeHash_182b4bf0 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_182b4bf0', iterfield = ['in_file'])

#Custom interface wrapping function Getusan
NodeHash_1a479090 = pe.MapNode(interface = firstlevelhelpers.Getusan, name = 'NodeName_1a479090', iterfield = ['brightness_thresh', 'in_file'])

#Wraps command **susan**
NodeHash_1a5fa380 = pe.MapNode(interface = fsl.SUSAN(), name = 'NodeName_1a5fa380', iterfield = ['brightness_threshold', 'in_file', 'usans'])
NodeHash_1a5fa380.inputs.dimension = 3
NodeHash_1a5fa380.inputs.fwhm = 5
NodeHash_1a5fa380.inputs.use_median = 1

#Wraps command **fslmaths**
NodeHash_1ba8b6a0 = pe.MapNode(interface = fsl.ApplyMask(), name = 'NodeName_1ba8b6a0', iterfield = ['in_file', 'mask_file'])

#Custom interface wrapping function Getinormscale
NodeHash_1b378470 = pe.MapNode(interface = firstlevelhelpers.Getinormscale, name = 'NodeName_1b378470', iterfield = ['medianval'])

#Wraps command **fslmaths**
NodeHash_1b3754f0 = pe.MapNode(interface = fsl.BinaryMaths(), name = 'NodeName_1b3754f0', iterfield = ['in_file', 'operand_value'])
NodeHash_1b3754f0.inputs.operation = 'mul'

#Wraps command **fslmaths**
NodeHash_1b252520 = pe.MapNode(interface = fsl.TemporalFilter(), name = 'NodeName_1b252520', iterfield = ['in_file'])
NodeHash_1b252520.inputs.highpass_sigma = 25

#Wraps command **fslmaths**
NodeHash_1cb2c540 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_1cb2c540', iterfield = ['in_file'])
NodeHash_1cb2c540.inputs.dimension = 'T'

#Wraps command **fslmaths**
NodeHash_1e361a00 = pe.MapNode(interface = fsl.BinaryMaths(), name = 'NodeName_1e361a00', iterfield = ['in_file', 'operand_file'])
NodeHash_1e361a00.inputs.operation = 'add'

#Makes a model specification compatible with spm/fsl designers.
NodeHash_1f14a780 = pe.MapNode(interface = modelgen.SpecifyModel(), name = 'NodeName_1f14a780', iterfield = ['functional_runs', 'subject_info'])
NodeHash_1f14a780.inputs.high_pass_filter_cutoff = 0
NodeHash_1f14a780.inputs.input_units = 'secs'
NodeHash_1f14a780.inputs.time_repetition = 2.0

#Generate FEAT specific files
NodeHash_1ee3fa40 = pe.MapNode(interface = fsl.Level1Design(), name = 'NodeName_1ee3fa40', iterfield = ['session_info'])
NodeHash_1ee3fa40.inputs.bases = {'dgamma':{'derivs': False}}
NodeHash_1ee3fa40.inputs.contrasts = [('con-incon', 'T', ['congruent_correct', 'congruent_correct'], [-1, 1])]
NodeHash_1ee3fa40.inputs.interscan_interval = 2.0
NodeHash_1ee3fa40.inputs.model_serial_correlations = True

#Wraps command **feat_model**
NodeHash_1ff83800 = pe.MapNode(interface = fsl.FEATModel(), name = 'NodeName_1ff83800', iterfield = ['ev_files', 'fsf_file'])

#Wraps command **film_gls**
NodeHash_215a5a10 = pe.MapNode(interface = fsl.FILMGLS(), name = 'NodeName_215a5a10', iterfield = ['design_file', 'in_file', 'tcon_file'])

#Wraps command **fslmaths**
NodeHash_218a6ba0 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_218a6ba0', iterfield = ['in_file'])
NodeHash_218a6ba0.inputs.dimension = 'T'

#Generic datasink module to store structured outputs
NodeHash_218b7a50 = pe.Node(interface = io.DataSink(), name = 'NodeName_218b7a50')
NodeHash_218b7a50.inputs.base_directory = '/tmp/FIRSTLEVEL'

#Basic interface class to select specific elements from a list
NodeHash_23ccf700 = pe.MapNode(interface = utility.Select(), name = 'NodeName_23ccf700', iterfield = ['inlist'])
NodeHash_23ccf700.inputs.index = 0

#Basic interface class to select specific elements from a list
NodeHash_f6fb890 = pe.MapNode(interface = utility.Select(), name = 'NodeName_f6fb890', iterfield = ['inlist'])
NodeHash_f6fb890.inputs.index = 0

#Generate subject specific second level model
NodeHash_245bbc70 = pe.Node(interface = fsl.L2Model(), name = 'NodeName_245bbc70')
NodeHash_245bbc70.inputs.num_copes = 20

#Custom interface wrapping function Find_fsl_mni_files
NodeHash_25021bd0 = pe.Node(interface = firstlevelhelpers.Find_fsl_mni_files, name = 'NodeName_25021bd0')

#Wraps command **flirt**
NodeHash_241acd10 = pe.MapNode(interface = fsl.FLIRT(), name = 'NodeName_241acd10', iterfield = ['in_file'])
NodeHash_241acd10.inputs.cost = 'corratio'
NodeHash_241acd10.inputs.dof = 12
NodeHash_241acd10.inputs.no_resample = True
NodeHash_241acd10.inputs.searchr_x = [-90, 90]
NodeHash_241acd10.inputs.searchr_y = [-90, 90]
NodeHash_241acd10.inputs.searchr_z = [-90, 90]

#Wraps command **convert_xfm**
NodeHash_25dce680 = pe.MapNode(interface = fsl.ConvertXFM(), name = 'NodeName_25dce680', iterfield = ['in_file', 'in_file2'])
NodeHash_25dce680.inputs.concat_xfm = True

#Wraps command **fnirt**
NodeHash_28f35280 = pe.MapNode(interface = fsl.FNIRT(), name = 'NodeName_28f35280', iterfield = ['in_file', 'affine_file'])
NodeHash_28f35280.inputs.field_file = True
NodeHash_28f35280.inputs.config_file = 'T1_2_MNI152_2mm'
NodeHash_28f35280.inputs.warp_resolution = (10, 10, 10)

#Wraps command **applywarp**
NodeHash_29d3f040 = pe.MapNode(interface = fsl.ApplyWarp(), name = 'NodeName_29d3f040', iterfield = ['field_file', 'in_file', 'premat'])
NodeHash_29d3f040.inputs.interp = 'trilinear'

#Wraps command **applywarp**
NodeHash_29ecf020 = pe.MapNode(interface = fsl.ApplyWarp(), name = 'NodeName_29ecf020', iterfield = ['field_file', 'in_file', 'premat'])
NodeHash_29ecf020.inputs.interp = 'trilinear'

#Wraps command **fslmerge**
NodeHash_2ceb9d10 = pe.Node(interface = fsl.Merge(), name = 'NodeName_2ceb9d10')
NodeHash_2ceb9d10.inputs.dimension = 't'

#Wraps command **flameo**
NodeHash_2f149160 = pe.Node(interface = fsl.FLAMEO(), name = 'NodeName_2f149160')
NodeHash_2f149160.inputs.run_mode = 'flame1'

#Wraps command **smoothest**
NodeHash_2fbc52b0 = pe.Node(interface = fsl.SmoothEstimate(), name = 'NodeName_2fbc52b0')

#Wraps command **cluster**
NodeHash_318a61d0 = pe.Node(interface = fsl.Cluster(), name = 'NodeName_318a61d0')
NodeHash_318a61d0.inputs.pthreshold = 0.05
NodeHash_318a61d0.inputs.threshold = 2.3

#Wraps command **fslmerge**
NodeHash_33749690 = pe.Node(interface = fsl.Merge(), name = 'NodeName_33749690')
NodeHash_33749690.inputs.dimension = 't'

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_1ad6ca0, 'anat', NodeHash_28f35280, 'in_file')
analysisflow.connect(NodeHash_1ad6ca0, 'anat', NodeHash_8f61130, 'reference')
analysisflow.connect(NodeHash_1ad6ca0, 'anat', NodeHash_2062490, 'in_file')
analysisflow.connect(NodeHash_1ad6ca0, 'events', NodeHash_127d16f0, 'in_file')
analysisflow.connect(NodeHash_1ad6ca0, 'func', NodeHash_c3ef3c0, 'in_file')
analysisflow.connect(NodeHash_1ad6ca0, 'func', NodeHash_4d25ff0, 'in_file')
analysisflow.connect(NodeHash_1a6ef50, 'sub_id', NodeHash_1ad6ca0, 'sub_id')
analysisflow.connect(NodeHash_2fbc52b0, 'volume', NodeHash_318a61d0, 'volume')
analysisflow.connect(NodeHash_2fbc52b0, 'dlh', NodeHash_318a61d0, 'dlh')
analysisflow.connect(NodeHash_33749690, 'merged_file', NodeHash_318a61d0, 'cope_file')
analysisflow.connect(NodeHash_2f149160, 'zstats', NodeHash_318a61d0, 'in_file')
analysisflow.connect(NodeHash_245bbc70, 'design_con', NodeHash_2f149160, 't_con_file')
analysisflow.connect(NodeHash_245bbc70, 'design_grp', NodeHash_2f149160, 'cov_split_file')
analysisflow.connect(NodeHash_245bbc70, 'design_mat', NodeHash_2f149160, 'design_file')
analysisflow.connect(NodeHash_2f149160, 'res4d', NodeHash_2fbc52b0, 'residual_fit_file')
analysisflow.connect(NodeHash_2ceb9d10, 'merged_file', NodeHash_2f149160, 'var_cope_file')
analysisflow.connect(NodeHash_f6fb890, 'out', NodeHash_29d3f040, 'in_file')
analysisflow.connect(NodeHash_33749690, 'merged_file', NodeHash_2f149160, 'cope_file')
analysisflow.connect(NodeHash_29d3f040, 'out_file', NodeHash_2ceb9d10, 'in_files')
analysisflow.connect(NodeHash_29ecf020, 'out_file', NodeHash_33749690, 'in_files')
analysisflow.connect(NodeHash_25dce680, 'out_file', NodeHash_29d3f040, 'premat')
analysisflow.connect(NodeHash_25dce680, 'out_file', NodeHash_29ecf020, 'premat')
analysisflow.connect(NodeHash_23ccf700, 'out', NodeHash_29ecf020, 'in_file')
analysisflow.connect(NodeHash_215a5a10, 'copes', NodeHash_23ccf700, 'inlist')
analysisflow.connect(NodeHash_215a5a10, 'varcopes', NodeHash_f6fb890, 'inlist')
analysisflow.connect(NodeHash_149ec020, 'out_stat', NodeHash_14e113c0, 'value')
analysisflow.connect(NodeHash_1b378470, 'value', NodeHash_1b3754f0, 'operand_value')
analysisflow.connect(NodeHash_182b4bf0, 'out_file', NodeHash_1a479090, 'in_file')
analysisflow.connect(NodeHash_149ec020, 'out_stat', NodeHash_14e3d7c0, 'value')
analysisflow.connect(NodeHash_14e3d7c0, 'out_val', NodeHash_157bd2b0, 'thresh')
analysisflow.connect(NodeHash_1a479090, 'usan', NodeHash_1a5fa380, 'usans')
analysisflow.connect(NodeHash_14e113c0, 'out_val', NodeHash_1a479090, 'brightness_thresh')
analysisflow.connect(NodeHash_14e113c0, 'out_val', NodeHash_1a5fa380, 'brightness_threshold')
analysisflow.connect(NodeHash_18508680, 'out_stat', NodeHash_1b378470, 'medianval')
analysisflow.connect(NodeHash_127d16f0, 'subject_info', NodeHash_1f14a780, 'subject_info')
analysisflow.connect(NodeHash_2062490, 'out_file', NodeHash_2e9d1d0, 'in_files')
analysisflow.connect(NodeHash_2e9d1d0, 'partial_volume_files', NodeHash_4ce0570, 'inlist')
analysisflow.connect(NodeHash_4ce0570, 'out', NodeHash_58c9230, 'in_file')
analysisflow.connect(NodeHash_58c9230, 'out_file', NodeHash_8f61130, 'wm_seg')
analysisflow.connect(NodeHash_2062490, 'out_file', NodeHash_79b5240, 'reference')
analysisflow.connect(NodeHash_79b5240, 'out_matrix_file', NodeHash_8f61130, 'in_matrix_file')
analysisflow.connect(NodeHash_2062490, 'out_file', NodeHash_241acd10, 'in_file')
analysisflow.connect(NodeHash_241acd10, 'out_matrix_file', NodeHash_25dce680, 'in_file2')
analysisflow.connect(NodeHash_8f61130, 'out_matrix_file', NodeHash_25dce680, 'in_file')
analysisflow.connect(NodeHash_4d25ff0, 'roi_file', NodeHash_c3ef3c0, 'ref_file')
analysisflow.connect(NodeHash_4d25ff0, 'roi_file', NodeHash_79b5240, 'in_file')
analysisflow.connect(NodeHash_c3ef3c0, 'par_file', NodeHash_c4a9c30, 'in_file')
analysisflow.connect(NodeHash_c3ef3c0, 'out_file', NodeHash_1040c610, 'in_file')
analysisflow.connect(NodeHash_1040c610, 'out_file', NodeHash_1212d0d0, 'in_file')
analysisflow.connect(NodeHash_1212d0d0, 'mask_file', NodeHash_1274e060, 'mask_file')
analysisflow.connect(NodeHash_c3ef3c0, 'out_file', NodeHash_1274e060, 'in_file')
analysisflow.connect(NodeHash_1274e060, 'out_file', NodeHash_149ec020, 'in_file')
analysisflow.connect(NodeHash_157bd2b0, 'out_file', NodeHash_15f74220, 'in_file')
analysisflow.connect(NodeHash_15f74220, 'out_file', NodeHash_16d421a0, 'in_file')
analysisflow.connect(NodeHash_16d421a0, 'out_file', NodeHash_18508680, 'mask_file')
analysisflow.connect(NodeHash_16d421a0, 'out_file', NodeHash_1801caa0, 'in_file')
analysisflow.connect(NodeHash_1274e060, 'out_file', NodeHash_157bd2b0, 'in_file')
analysisflow.connect(NodeHash_c3ef3c0, 'out_file', NodeHash_18508680, 'in_file')
analysisflow.connect(NodeHash_c3ef3c0, 'out_file', NodeHash_181e69e0, 'in_file')
analysisflow.connect(NodeHash_1801caa0, 'out_file', NodeHash_181e69e0, 'mask_file')
analysisflow.connect(NodeHash_181e69e0, 'out_file', NodeHash_182b4bf0, 'in_file')
analysisflow.connect(NodeHash_181e69e0, 'out_file', NodeHash_1a5fa380, 'in_file')
analysisflow.connect(NodeHash_1a5fa380, 'smoothed_file', NodeHash_1ba8b6a0, 'in_file')
analysisflow.connect(NodeHash_1801caa0, 'out_file', NodeHash_1ba8b6a0, 'mask_file')
analysisflow.connect(NodeHash_1ba8b6a0, 'out_file', NodeHash_1b3754f0, 'in_file')
analysisflow.connect(NodeHash_1b3754f0, 'out_file', NodeHash_1cb2c540, 'in_file')
analysisflow.connect(NodeHash_1b3754f0, 'out_file', NodeHash_1b252520, 'in_file')
analysisflow.connect(NodeHash_1b252520, 'out_file', NodeHash_1e361a00, 'in_file')
analysisflow.connect(NodeHash_1cb2c540, 'out_file', NodeHash_1e361a00, 'operand_file')
analysisflow.connect(NodeHash_1e361a00, 'out_file', NodeHash_218a6ba0, 'in_file')
analysisflow.connect(NodeHash_1e361a00, 'out_file', NodeHash_1f14a780, 'functional_runs')
analysisflow.connect(NodeHash_1f14a780, 'session_info', NodeHash_1ee3fa40, 'session_info')
analysisflow.connect(NodeHash_1ee3fa40, 'fsf_files', NodeHash_1ff83800, 'fsf_file')
analysisflow.connect(NodeHash_1ee3fa40, 'ev_files', NodeHash_1ff83800, 'ev_files')
analysisflow.connect(NodeHash_1ff83800, 'con_file', NodeHash_215a5a10, 'tcon_file')
analysisflow.connect(NodeHash_1ff83800, 'design_file', NodeHash_215a5a10, 'design_file')
analysisflow.connect(NodeHash_1e361a00, 'out_file', NodeHash_215a5a10, 'in_file')
analysisflow.connect(NodeHash_215a5a10, 'results_dir', NodeHash_218b7a50, 'firstlevel')
analysisflow.connect(NodeHash_4d25ff0, 'roi_file', NodeHash_8f61130, 'in_file')
analysisflow.connect(NodeHash_241acd10, 'out_matrix_file', NodeHash_28f35280, 'affine_file')
analysisflow.connect(NodeHash_28f35280, 'field_file', NodeHash_29d3f040, 'field_file')
analysisflow.connect(NodeHash_28f35280, 'field_file', NodeHash_29ecf020, 'field_file')
analysisflow.connect(NodeHash_25021bd0, 'MNI_brain', NodeHash_241acd10, 'reference')
analysisflow.connect(NodeHash_25021bd0, 'MNI_mask', NodeHash_28f35280, 'refmask_file')
analysisflow.connect(NodeHash_25021bd0, 'MNI_mask', NodeHash_2fbc52b0, 'mask_file')
analysisflow.connect(NodeHash_25021bd0, 'MNI_mask', NodeHash_2f149160, 'mask_file')
analysisflow.connect(NodeHash_25021bd0, 'MNI_head', NodeHash_28f35280, 'ref_file')
analysisflow.connect(NodeHash_25021bd0, 'MNI_brain', NodeHash_29d3f040, 'ref_file')
analysisflow.connect(NodeHash_25021bd0, 'MNI_brain', NodeHash_29ecf020, 'ref_file')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 10} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
