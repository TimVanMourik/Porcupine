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
NodeHash_2c4dda0 = pe.Node(utility.IdentityInterface(fields=['sub_id']), name = 'NodeName_2c4dda0')
NodeHash_2c4dda0.inputs.sub_id = ['sub-02', 'sub-03', 'sub-04', 'sub-05', 'sub-06', 'sub-07', 'sub-08', 'sub-09', 'sub-10', 'sub-11', 'sub-12', 'sub-13', 'sub-14', 'sub-15', 'sub-16', 'sub-17', 'sub-18', 'sub-19', 'sub-20', 'sub-21']

#Generic datagrabber module that wraps around glob in an
NodeHash_17173a00 = pe.MapNode(io.S3DataGrabber(infields=['field_template','sub_id'], outfields=['func','events','anat']), name = 'NodeName_17173a00', iterfield = ['sub_id'])
NodeHash_17173a00.inputs.anon = True
NodeHash_17173a00.inputs.bucket = 'openneuro'
NodeHash_17173a00.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_17173a00.inputs.local_directory = '/tmp'
NodeHash_17173a00.inputs.sort_filelist = True
NodeHash_17173a00.inputs.template = '*'
NodeHash_17173a00.inputs.template_args = dict(func=[['sub_id', 'sub_id']], events=[['sub_id', 'sub_id']], anat=[['sub_id', 'sub_id']])
NodeHash_17173a00.inputs.field_template = dict(func='%s/func/%s_task-simon_run-1_bold.nii.gz', events='%s/func/%s_task-simon_run-1_events.tsv', anat='%s/anat/%s_T1w.nii.gz')

#Wraps command **bet**
NodeHash_20af2180 = pe.MapNode(interface = fsl.BET(), name = 'NodeName_20af2180', iterfield = ['in_file'])
NodeHash_20af2180.inputs.frac = 0.3
NodeHash_20af2180.inputs.robust = True

#Wraps command **fast**
NodeHash_10d41ed0 = pe.MapNode(interface = fsl.FAST(), name = 'NodeName_10d41ed0', iterfield = ['in_files'])

#Basic interface class to select specific elements from a list
NodeHash_282e9070 = pe.MapNode(interface = utility.Select(), name = 'NodeName_282e9070', iterfield = ['inlist'])
NodeHash_282e9070.inputs.index = 2

#Wraps command **fslmaths**
NodeHash_313f8780 = pe.MapNode(interface = fsl.Threshold(), name = 'NodeName_313f8780', iterfield = ['in_file'])
NodeHash_313f8780.inputs.args = '-bin'
NodeHash_313f8780.inputs.thresh = 0.5

#Wraps command **fslroi**
NodeHash_1af07380 = pe.MapNode(interface = fsl.ExtractROI(), name = 'NodeName_1af07380', iterfield = ['in_file'])
NodeHash_1af07380.inputs.t_min = 1
NodeHash_1af07380.inputs.t_size = 1

#Wraps command **flirt**
NodeHash_5accf90 = pe.MapNode(interface = fsl.FLIRT(), name = 'NodeName_5accf90', iterfield = ['in_file', 'reference'])

#Wraps command **flirt**
NodeHash_22c888c0 = pe.MapNode(interface = fsl.FLIRT(), name = 'NodeName_22c888c0', iterfield = ['in_file', 'in_matrix_file', 'reference', 'wm_seg'])
NodeHash_22c888c0.inputs.cost = 'bbr'
NodeHash_22c888c0.inputs.dof = 6
NodeHash_22c888c0.inputs.no_resample = True

#Wraps command **mcflirt**
NodeHash_32896ec0 = pe.MapNode(interface = fsl.MCFLIRT(), name = 'NodeName_32896ec0', iterfield = ['in_file', 'ref_file'])
NodeHash_32896ec0.inputs.interpolation = 'spline'
NodeHash_32896ec0.inputs.save_mats = True
NodeHash_32896ec0.inputs.save_plots = True
NodeHash_32896ec0.inputs.save_rms = True

#Wraps command **fsl_tsplot**
NodeHash_2a03f5c0 = pe.MapNode(interface = fsl.PlotMotionParams(), name = 'NodeName_2a03f5c0', iterfield = ['in_file'])
NodeHash_2a03f5c0.inputs.args = '-a x,y,z -w 640 -h 144'
NodeHash_2a03f5c0.inputs.in_source = 'fsl'
NodeHash_2a03f5c0.iterables = [('plot_type', ['rotations', 'translations'])]

#Wraps command **fslmaths**
NodeHash_22a97680 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_22a97680', iterfield = ['in_file'])
NodeHash_22a97680.inputs.dimension = 'T'

#Wraps command **bet**
NodeHash_55ea000 = pe.MapNode(interface = fsl.BET(), name = 'NodeName_55ea000', iterfield = ['in_file'])
NodeHash_55ea000.inputs.frac = 0.3
NodeHash_55ea000.inputs.mask = True
NodeHash_55ea000.inputs.no_output = True

#Wraps command **fslmaths**
NodeHash_20069a90 = pe.MapNode(interface = fsl.ApplyMask(), name = 'NodeName_20069a90', iterfield = ['in_file', 'mask_file'])

#Wraps command **fslstats**
NodeHash_22629c10 = pe.MapNode(interface = fsl.ImageStats(), name = 'NodeName_22629c10', iterfield = ['in_file'])
NodeHash_22629c10.inputs.op_string = '-p 98'

#Custom interface wrapping function Tsv2subjectinfo
NodeHash_1ad39010 = pe.MapNode(interface = firstlevelhelpers.Tsv2subjectinfo, name = 'NodeName_1ad39010', iterfield = ['in_file'])

#Custom interface wrapping function Getpercentthresh
NodeHash_1cecfcd0 = pe.MapNode(interface = firstlevelhelpers.Getpercentthresh, name = 'NodeName_1cecfcd0', iterfield = ['value'])
NodeHash_1cecfcd0.inputs.percentage = 0.75

#Custom interface wrapping function Getpercentthresh
NodeHash_20695ac0 = pe.MapNode(interface = firstlevelhelpers.Getpercentthresh, name = 'NodeName_20695ac0', iterfield = ['value'])
NodeHash_20695ac0.inputs.percentage = 0.1

#Wraps command **fslmaths**
NodeHash_10ff9c60 = pe.MapNode(interface = fsl.Threshold(), name = 'NodeName_10ff9c60', iterfield = ['in_file', 'thresh'])

#Wraps command **fslmaths**
NodeHash_843b4a0 = pe.MapNode(interface = fsl.MinImage(), name = 'NodeName_843b4a0', iterfield = ['in_file'])
NodeHash_843b4a0.inputs.args = '-bin'
NodeHash_843b4a0.inputs.dimension = 'T'

#Wraps command **fslmaths**
NodeHash_2b6977b0 = pe.MapNode(interface = fsl.ChangeDataType(), name = 'NodeName_2b6977b0', iterfield = ['in_file'])
NodeHash_2b6977b0.inputs.output_datatype = 'char'

#Wraps command **fslmaths**
NodeHash_258767c0 = pe.MapNode(interface = fsl.DilateImage(), name = 'NodeName_258767c0', iterfield = ['in_file'])
NodeHash_258767c0.inputs.operation = 'max'

#Wraps command **fslstats**
NodeHash_2fd0bda0 = pe.MapNode(interface = fsl.ImageStats(), name = 'NodeName_2fd0bda0', iterfield = ['in_file', 'mask_file'])
NodeHash_2fd0bda0.inputs.op_string = '-p 50'

#Wraps command **fslmaths**
NodeHash_ffd7a90 = pe.MapNode(interface = fsl.ApplyMask(), name = 'NodeName_ffd7a90', iterfield = ['in_file', 'mask_file'])

#Wraps command **fslmaths**
NodeHash_255ee520 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_255ee520', iterfield = ['in_file'])

#Custom interface wrapping function Getusan
NodeHash_12d6d9d0 = pe.MapNode(interface = firstlevelhelpers.Getusan, name = 'NodeName_12d6d9d0', iterfield = ['brightness_thresh', 'in_file'])

#Wraps command **susan**
NodeHash_f58d230 = pe.MapNode(interface = fsl.SUSAN(), name = 'NodeName_f58d230', iterfield = ['brightness_threshold', 'in_file', 'usans'])
NodeHash_f58d230.inputs.dimension = 3
NodeHash_f58d230.inputs.fwhm = 5
NodeHash_f58d230.inputs.use_median = 1

#Wraps command **fslmaths**
NodeHash_10dc3c10 = pe.MapNode(interface = fsl.ApplyMask(), name = 'NodeName_10dc3c10', iterfield = ['in_file', 'mask_file'])

#Custom interface wrapping function Getinormscale
NodeHash_1c9d2280 = pe.MapNode(interface = firstlevelhelpers.Getinormscale, name = 'NodeName_1c9d2280', iterfield = ['medianval'])

#Wraps command **fslmaths**
NodeHash_2ee27f90 = pe.MapNode(interface = fsl.BinaryMaths(), name = 'NodeName_2ee27f90', iterfield = ['in_file', 'operand_value'])
NodeHash_2ee27f90.inputs.operation = 'mul'

#Wraps command **fslmaths**
NodeHash_c0d1e30 = pe.MapNode(interface = fsl.TemporalFilter(), name = 'NodeName_c0d1e30', iterfield = ['in_file'])
NodeHash_c0d1e30.inputs.highpass_sigma = 25

#Wraps command **fslmaths**
NodeHash_17446a20 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_17446a20', iterfield = ['in_file'])
NodeHash_17446a20.inputs.dimension = 'T'

#Wraps command **fslmaths**
NodeHash_b5a5810 = pe.MapNode(interface = fsl.BinaryMaths(), name = 'NodeName_b5a5810', iterfield = ['in_file', 'operand_file'])
NodeHash_b5a5810.inputs.operation = 'add'

#Makes a model specification compatible with spm/fsl designers.
NodeHash_1e7a3420 = pe.MapNode(interface = modelgen.SpecifyModel(), name = 'NodeName_1e7a3420', iterfield = ['functional_runs', 'subject_info'])
NodeHash_1e7a3420.inputs.high_pass_filter_cutoff = 0
NodeHash_1e7a3420.inputs.input_units = 'secs'
NodeHash_1e7a3420.inputs.time_repetition = 2.0

#Generate FEAT specific files
NodeHash_9bb0d40 = pe.MapNode(interface = fsl.Level1Design(), name = 'NodeName_9bb0d40', iterfield = ['session_info'])
NodeHash_9bb0d40.inputs.bases = {'dgamma':{'derivs': False}}
NodeHash_9bb0d40.inputs.contrasts = [('con-incon', 'T', ['congruent_correct', 'congruent_correct'], [-1, 1])]
NodeHash_9bb0d40.inputs.interscan_interval = 2.0
NodeHash_9bb0d40.inputs.model_serial_correlations = True

#Wraps command **feat_model**
NodeHash_6b33f50 = pe.MapNode(interface = fsl.FEATModel(), name = 'NodeName_6b33f50', iterfield = ['ev_files', 'fsf_file'])

#Wraps command **film_gls**
NodeHash_2762fb60 = pe.MapNode(interface = fsl.FILMGLS(), name = 'NodeName_2762fb60', iterfield = ['design_file', 'in_file', 'tcon_file'])

#Wraps command **fslmaths**
NodeHash_2df82970 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_2df82970', iterfield = ['in_file'])
NodeHash_2df82970.inputs.dimension = 'T'

#Generic datasink module to store structured outputs
NodeHash_33a4bec0 = pe.Node(interface = io.DataSink(), name = 'NodeName_33a4bec0')
NodeHash_33a4bec0.inputs.base_directory = '/tmp/FIRSTLEVEL'

#Basic interface class to select specific elements from a list
NodeHash_7caa820 = pe.MapNode(interface = utility.Select(), name = 'NodeName_7caa820', iterfield = ['inlist'])
NodeHash_7caa820.inputs.index = 0

#Basic interface class to select specific elements from a list
NodeHash_b8ed090 = pe.MapNode(interface = utility.Select(), name = 'NodeName_b8ed090', iterfield = ['inlist'])
NodeHash_b8ed090.inputs.index = 0

#Generate subject specific second level model
NodeHash_3e74ed0 = pe.Node(interface = fsl.L2Model(), name = 'NodeName_3e74ed0')
NodeHash_3e74ed0.inputs.num_copes = 20

#Custom interface wrapping function Find_fsl_mni_files
NodeHash_2e292140 = pe.Node(interface = firstlevelhelpers.Find_fsl_mni_files, name = 'NodeName_2e292140')

#Wraps command **flirt**
NodeHash_2c370b0 = pe.MapNode(interface = fsl.FLIRT(), name = 'NodeName_2c370b0', iterfield = ['in_file'])
NodeHash_2c370b0.inputs.cost = 'corratio'
NodeHash_2c370b0.inputs.dof = 12
NodeHash_2c370b0.inputs.no_resample = True
NodeHash_2c370b0.inputs.searchr_x = [-90, 90]
NodeHash_2c370b0.inputs.searchr_y = [-90, 90]
NodeHash_2c370b0.inputs.searchr_z = [-90, 90]

#Wraps command **convert_xfm**
NodeHash_2528e3a0 = pe.MapNode(interface = fsl.ConvertXFM(), name = 'NodeName_2528e3a0', iterfield = ['in_file', 'in_file2'])
NodeHash_2528e3a0.inputs.concat_xfm = True

#Wraps command **fnirt**
NodeHash_1e7cc750 = pe.MapNode(interface = fsl.FNIRT(), name = 'NodeName_1e7cc750', iterfield = ['in_file', 'affine_file'])
NodeHash_1e7cc750.inputs.field_file = True
NodeHash_1e7cc750.inputs.config_file = 'T1_2_MNI152_2mm'
NodeHash_1e7cc750.inputs.warp_resolution = (10, 10, 10)

#Wraps command **applywarp**
NodeHash_347043c0 = pe.MapNode(interface = fsl.ApplyWarp(), name = 'NodeName_347043c0', iterfield = ['field_file', 'in_file', 'premat'])
NodeHash_347043c0.inputs.interp = 'trilinear'

#Wraps command **applywarp**
NodeHash_d73fcb0 = pe.MapNode(interface = fsl.ApplyWarp(), name = 'NodeName_d73fcb0', iterfield = ['field_file', 'in_file', 'premat'])
NodeHash_d73fcb0.inputs.interp = 'trilinear'

#Wraps command **fslmerge**
NodeHash_264457d0 = pe.Node(interface = fsl.Merge(), name = 'NodeName_264457d0')
NodeHash_264457d0.inputs.dimension = 't'

#Wraps command **flameo**
NodeHash_882ac40 = pe.Node(interface = fsl.FLAMEO(), name = 'NodeName_882ac40')
NodeHash_882ac40.inputs.run_mode = 'flame1'

#Wraps command **smoothest**
NodeHash_33f1eba0 = pe.Node(interface = fsl.SmoothEstimate(), name = 'NodeName_33f1eba0')

#Wraps command **cluster**
NodeHash_1978f9c0 = pe.Node(interface = fsl.Cluster(), name = 'NodeName_1978f9c0')
NodeHash_1978f9c0.inputs.pthreshold = 0.05
NodeHash_1978f9c0.inputs.threshold = 2.3

#Wraps command **fslmerge**
NodeHash_3c0ae30 = pe.Node(interface = fsl.Merge(), name = 'NodeName_3c0ae30')
NodeHash_3c0ae30.inputs.dimension = 't'

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_2e292140, 'MNI_brain', NodeHash_d73fcb0, 'ref_file')
analysisflow.connect(NodeHash_2e292140, 'MNI_brain', NodeHash_347043c0, 'ref_file')
analysisflow.connect(NodeHash_2e292140, 'MNI_head', NodeHash_1e7cc750, 'ref_file')
analysisflow.connect(NodeHash_2e292140, 'MNI_mask', NodeHash_882ac40, 'mask_file')
analysisflow.connect(NodeHash_2e292140, 'MNI_mask', NodeHash_33f1eba0, 'mask_file')
analysisflow.connect(NodeHash_2e292140, 'MNI_mask', NodeHash_1e7cc750, 'refmask_file')
analysisflow.connect(NodeHash_2e292140, 'MNI_brain', NodeHash_2c370b0, 'reference')
analysisflow.connect(NodeHash_1e7cc750, 'field_file', NodeHash_d73fcb0, 'field_file')
analysisflow.connect(NodeHash_1e7cc750, 'field_file', NodeHash_347043c0, 'field_file')
analysisflow.connect(NodeHash_2c370b0, 'out_matrix_file', NodeHash_1e7cc750, 'affine_file')
analysisflow.connect(NodeHash_1af07380, 'roi_file', NodeHash_22c888c0, 'in_file')
analysisflow.connect(NodeHash_2762fb60, 'results_dir', NodeHash_33a4bec0, 'firstlevel')
analysisflow.connect(NodeHash_b5a5810, 'out_file', NodeHash_2762fb60, 'in_file')
analysisflow.connect(NodeHash_6b33f50, 'design_file', NodeHash_2762fb60, 'design_file')
analysisflow.connect(NodeHash_6b33f50, 'con_file', NodeHash_2762fb60, 'tcon_file')
analysisflow.connect(NodeHash_9bb0d40, 'ev_files', NodeHash_6b33f50, 'ev_files')
analysisflow.connect(NodeHash_9bb0d40, 'fsf_files', NodeHash_6b33f50, 'fsf_file')
analysisflow.connect(NodeHash_1e7a3420, 'session_info', NodeHash_9bb0d40, 'session_info')
analysisflow.connect(NodeHash_b5a5810, 'out_file', NodeHash_1e7a3420, 'functional_runs')
analysisflow.connect(NodeHash_b5a5810, 'out_file', NodeHash_2df82970, 'in_file')
analysisflow.connect(NodeHash_17446a20, 'out_file', NodeHash_b5a5810, 'operand_file')
analysisflow.connect(NodeHash_c0d1e30, 'out_file', NodeHash_b5a5810, 'in_file')
analysisflow.connect(NodeHash_2ee27f90, 'out_file', NodeHash_c0d1e30, 'in_file')
analysisflow.connect(NodeHash_2ee27f90, 'out_file', NodeHash_17446a20, 'in_file')
analysisflow.connect(NodeHash_10dc3c10, 'out_file', NodeHash_2ee27f90, 'in_file')
analysisflow.connect(NodeHash_258767c0, 'out_file', NodeHash_10dc3c10, 'mask_file')
analysisflow.connect(NodeHash_f58d230, 'smoothed_file', NodeHash_10dc3c10, 'in_file')
analysisflow.connect(NodeHash_ffd7a90, 'out_file', NodeHash_f58d230, 'in_file')
analysisflow.connect(NodeHash_ffd7a90, 'out_file', NodeHash_255ee520, 'in_file')
analysisflow.connect(NodeHash_258767c0, 'out_file', NodeHash_ffd7a90, 'mask_file')
analysisflow.connect(NodeHash_32896ec0, 'out_file', NodeHash_ffd7a90, 'in_file')
analysisflow.connect(NodeHash_32896ec0, 'out_file', NodeHash_2fd0bda0, 'in_file')
analysisflow.connect(NodeHash_20069a90, 'out_file', NodeHash_10ff9c60, 'in_file')
analysisflow.connect(NodeHash_2b6977b0, 'out_file', NodeHash_258767c0, 'in_file')
analysisflow.connect(NodeHash_2b6977b0, 'out_file', NodeHash_2fd0bda0, 'mask_file')
analysisflow.connect(NodeHash_843b4a0, 'out_file', NodeHash_2b6977b0, 'in_file')
analysisflow.connect(NodeHash_10ff9c60, 'out_file', NodeHash_843b4a0, 'in_file')
analysisflow.connect(NodeHash_20069a90, 'out_file', NodeHash_22629c10, 'in_file')
analysisflow.connect(NodeHash_32896ec0, 'out_file', NodeHash_20069a90, 'in_file')
analysisflow.connect(NodeHash_55ea000, 'mask_file', NodeHash_20069a90, 'mask_file')
analysisflow.connect(NodeHash_22a97680, 'out_file', NodeHash_55ea000, 'in_file')
analysisflow.connect(NodeHash_32896ec0, 'out_file', NodeHash_22a97680, 'in_file')
analysisflow.connect(NodeHash_32896ec0, 'par_file', NodeHash_2a03f5c0, 'in_file')
analysisflow.connect(NodeHash_1af07380, 'roi_file', NodeHash_5accf90, 'in_file')
analysisflow.connect(NodeHash_1af07380, 'roi_file', NodeHash_32896ec0, 'ref_file')
analysisflow.connect(NodeHash_22c888c0, 'out_matrix_file', NodeHash_2528e3a0, 'in_file')
analysisflow.connect(NodeHash_2c370b0, 'out_matrix_file', NodeHash_2528e3a0, 'in_file2')
analysisflow.connect(NodeHash_20af2180, 'out_file', NodeHash_2c370b0, 'in_file')
analysisflow.connect(NodeHash_5accf90, 'out_matrix_file', NodeHash_22c888c0, 'in_matrix_file')
analysisflow.connect(NodeHash_20af2180, 'out_file', NodeHash_5accf90, 'reference')
analysisflow.connect(NodeHash_313f8780, 'out_file', NodeHash_22c888c0, 'wm_seg')
analysisflow.connect(NodeHash_282e9070, 'out', NodeHash_313f8780, 'in_file')
analysisflow.connect(NodeHash_10d41ed0, 'partial_volume_files', NodeHash_282e9070, 'inlist')
analysisflow.connect(NodeHash_20af2180, 'out_file', NodeHash_10d41ed0, 'in_files')
analysisflow.connect(NodeHash_1ad39010, 'subject_info', NodeHash_1e7a3420, 'subject_info')
analysisflow.connect(NodeHash_2fd0bda0, 'out_stat', NodeHash_1c9d2280, 'medianval')
analysisflow.connect(NodeHash_1cecfcd0, 'out_val', NodeHash_f58d230, 'brightness_threshold')
analysisflow.connect(NodeHash_1cecfcd0, 'out_val', NodeHash_12d6d9d0, 'brightness_thresh')
analysisflow.connect(NodeHash_12d6d9d0, 'usan', NodeHash_f58d230, 'usans')
analysisflow.connect(NodeHash_20695ac0, 'out_val', NodeHash_10ff9c60, 'thresh')
analysisflow.connect(NodeHash_22629c10, 'out_stat', NodeHash_20695ac0, 'value')
analysisflow.connect(NodeHash_255ee520, 'out_file', NodeHash_12d6d9d0, 'in_file')
analysisflow.connect(NodeHash_1c9d2280, 'value', NodeHash_2ee27f90, 'operand_value')
analysisflow.connect(NodeHash_22629c10, 'out_stat', NodeHash_1cecfcd0, 'value')
analysisflow.connect(NodeHash_2762fb60, 'varcopes', NodeHash_b8ed090, 'inlist')
analysisflow.connect(NodeHash_2762fb60, 'copes', NodeHash_7caa820, 'inlist')
analysisflow.connect(NodeHash_7caa820, 'out', NodeHash_d73fcb0, 'in_file')
analysisflow.connect(NodeHash_2528e3a0, 'out_file', NodeHash_d73fcb0, 'premat')
analysisflow.connect(NodeHash_2528e3a0, 'out_file', NodeHash_347043c0, 'premat')
analysisflow.connect(NodeHash_d73fcb0, 'out_file', NodeHash_3c0ae30, 'in_files')
analysisflow.connect(NodeHash_347043c0, 'out_file', NodeHash_264457d0, 'in_files')
analysisflow.connect(NodeHash_3c0ae30, 'merged_file', NodeHash_882ac40, 'cope_file')
analysisflow.connect(NodeHash_b8ed090, 'out', NodeHash_347043c0, 'in_file')
analysisflow.connect(NodeHash_264457d0, 'merged_file', NodeHash_882ac40, 'var_cope_file')
analysisflow.connect(NodeHash_882ac40, 'tdof', NodeHash_33f1eba0, 'dof')
analysisflow.connect(NodeHash_882ac40, 'res4d', NodeHash_33f1eba0, 'residual_fit_file')
analysisflow.connect(NodeHash_3e74ed0, 'design_mat', NodeHash_882ac40, 'design_file')
analysisflow.connect(NodeHash_3e74ed0, 'design_grp', NodeHash_882ac40, 'cov_split_file')
analysisflow.connect(NodeHash_3e74ed0, 'design_con', NodeHash_882ac40, 't_con_file')
analysisflow.connect(NodeHash_882ac40, 'zstats', NodeHash_1978f9c0, 'in_file')
analysisflow.connect(NodeHash_3c0ae30, 'merged_file', NodeHash_1978f9c0, 'cope_file')
analysisflow.connect(NodeHash_33f1eba0, 'dlh', NodeHash_1978f9c0, 'dlh')
analysisflow.connect(NodeHash_33f1eba0, 'volume', NodeHash_1978f9c0, 'volume')
analysisflow.connect(NodeHash_2c4dda0, 'sub_id', NodeHash_17173a00, 'sub_id')
analysisflow.connect(NodeHash_17173a00, 'func', NodeHash_1af07380, 'in_file')
analysisflow.connect(NodeHash_17173a00, 'func', NodeHash_32896ec0, 'in_file')
analysisflow.connect(NodeHash_17173a00, 'events', NodeHash_1ad39010, 'in_file')
analysisflow.connect(NodeHash_17173a00, 'anat', NodeHash_20af2180, 'in_file')
analysisflow.connect(NodeHash_17173a00, 'anat', NodeHash_22c888c0, 'reference')
analysisflow.connect(NodeHash_17173a00, 'anat', NodeHash_1e7cc750, 'in_file')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 10} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
