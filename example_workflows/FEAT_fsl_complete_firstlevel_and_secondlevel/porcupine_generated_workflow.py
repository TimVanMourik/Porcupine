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
NodeHash_2f2a810 = pe.Node(utility.IdentityInterface(fields=['sub_id']), name = 'NodeName_2f2a810')
NodeHash_2f2a810.inputs.sub_id = ['sub-02', 'sub-03', 'sub-04', 'sub-05', 'sub-06', 'sub-07', 'sub-08', 'sub-09', 'sub-10', 'sub-11', 'sub-12', 'sub-13', 'sub-14', 'sub-15', 'sub-16', 'sub-17', 'sub-18', 'sub-19', 'sub-20', 'sub-21']

#Flexibly collect data from disk to feed into workflows.
NodeHash_33a30f0 = pe.MapNode(io.SelectFiles(templates={'anat':'{sub_id}/anat/{sub_id}_T1w.nii.gz','events':'{sub_id}/func/{sub_id}_task-simon_run-1_events.tsv','func':'{sub_id}/func/{sub_id}_task-simon_run-1_bold.nii.gz'}), name = 'NodeName_33a30f0', iterfield = ['sub_id'])
NodeHash_33a30f0.inputs.base_directory = '/media/lukas/goliath/Porcupine/example_workflows/example_data'
NodeHash_33a30f0.inputs.sort_filelist = True

#Generic datagrabber module that wraps around glob in an
NodeHash_33d85d0 = pe.Node(io.S3DataGrabber(outfields=['outfiles']), name = 'NodeName_33d85d0')
NodeHash_33d85d0.inputs.anon = True
NodeHash_33d85d0.inputs.bucket = 'openneuro'
NodeHash_33d85d0.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_33d85d0.inputs.local_directory = '/tmp'
NodeHash_33d85d0.inputs.sort_filelist = True
NodeHash_33d85d0.inputs.template = 'sub-01/func/sub-01_task-simon_run-1_bold.nii.gz'

#Generic datagrabber module that wraps around glob in an
NodeHash_38ee6e0 = pe.Node(io.S3DataGrabber(outfields=['outfiles']), name = 'NodeName_38ee6e0')
NodeHash_38ee6e0.inputs.anon = True
NodeHash_38ee6e0.inputs.bucket = 'openneuro'
NodeHash_38ee6e0.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_38ee6e0.inputs.local_directory = '/tmp'
NodeHash_38ee6e0.inputs.sort_filelist = True
NodeHash_38ee6e0.inputs.template = 'sub-01/anat/sub-01_T1w.nii.gz'

#Generic datagrabber module that wraps around glob in an
NodeHash_441abe0 = pe.Node(io.S3DataGrabber(outfields=['events']), name = 'NodeName_441abe0')
NodeHash_441abe0.inputs.anon = True
NodeHash_441abe0.inputs.bucket = 'openneuro'
NodeHash_441abe0.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_441abe0.inputs.local_directory = '/tmp'
NodeHash_441abe0.inputs.sort_filelist = True
NodeHash_441abe0.inputs.template = 'sub-01/func/sub-01_task-simon_run-1_events.tsv'

#Basic interface class generates identity mappings
NodeHash_416fbf0 = pe.Node(utility.IdentityInterface(fields=['MNI_brain','MNI_head','MNI_mask']), name = 'NodeName_416fbf0')
NodeHash_416fbf0.inputs.MNI_brain = '/usr/share/fsl/5.0/data/standard/MNI152_T1_2mm_brain.nii.gz'
NodeHash_416fbf0.inputs.MNI_head = '/usr/share/fsl/5.0/data/standard/MNI152_T1_2mm.nii.gz'
NodeHash_416fbf0.inputs.MNI_mask = '/usr/share/fsl/5.0/data/standard/MNI152_T1_2mm_brain_mask_dil.nii.gz'

#Wraps command **bet**
NodeHash_559ee70 = pe.MapNode(interface = fsl.BET(), name = 'NodeName_559ee70', iterfield = ['in_file'])
NodeHash_559ee70.inputs.frac = 0.3
NodeHash_559ee70.inputs.robust = True

#Wraps command **fast**
NodeHash_65ebc70 = pe.MapNode(interface = fsl.FAST(), name = 'NodeName_65ebc70', iterfield = ['in_files'])

#Basic interface class to select specific elements from a list
NodeHash_9765120 = pe.MapNode(interface = utility.Select(), name = 'NodeName_9765120', iterfield = ['inlist'])
NodeHash_9765120.inputs.index = 2

#Wraps command **fslmaths**
NodeHash_8541900 = pe.MapNode(interface = fsl.Threshold(), name = 'NodeName_8541900', iterfield = ['in_file'])
NodeHash_8541900.inputs.args = '-bin'
NodeHash_8541900.inputs.thresh = 0.5

#Wraps command **flirt**
NodeHash_a538a30 = pe.MapNode(interface = fsl.FLIRT(), name = 'NodeName_a538a30', iterfield = ['in_file'])
NodeHash_a538a30.inputs.cost = 'corratio'
NodeHash_a538a30.inputs.dof = 12
NodeHash_a538a30.inputs.no_resample = True
NodeHash_a538a30.inputs.searchr_x = [-90, 90]
NodeHash_a538a30.inputs.searchr_y = [-90, 90]
NodeHash_a538a30.inputs.searchr_z = [-90, 90]

#Wraps command **fslroi**
NodeHash_caf1be0 = pe.MapNode(interface = fsl.ExtractROI(), name = 'NodeName_caf1be0', iterfield = ['in_file'])
NodeHash_caf1be0.inputs.t_min = 1
NodeHash_caf1be0.inputs.t_size = 1

#Wraps command **flirt**
NodeHash_eb37a70 = pe.MapNode(interface = fsl.FLIRT(), name = 'NodeName_eb37a70', iterfield = ['in_file', 'reference'])

#Wraps command **flirt**
NodeHash_fa474b0 = pe.MapNode(interface = fsl.FLIRT(), name = 'NodeName_fa474b0', iterfield = ['in_file', 'in_matrix_file', 'reference', 'wm_seg'])
NodeHash_fa474b0.inputs.cost = 'bbr'
NodeHash_fa474b0.inputs.dof = 6
NodeHash_fa474b0.inputs.no_resample = True

#Wraps command **fnirt**
NodeHash_12fba730 = pe.MapNode(interface = fsl.FNIRT(), name = 'NodeName_12fba730', iterfield = ['in_file', 'affine_file'])
NodeHash_12fba730.inputs.field_file = True
NodeHash_12fba730.inputs.config_file = 'T1_2_MNI152_2mm'
NodeHash_12fba730.inputs.warp_resolution = (10, 10, 10)

#Wraps command **convert_xfm**
NodeHash_169ead00 = pe.MapNode(interface = fsl.ConvertXFM(), name = 'NodeName_169ead00', iterfield = ['in_file', 'in_file2'])
NodeHash_169ead00.inputs.concat_xfm = True

#Wraps command **mcflirt**
NodeHash_17dcb750 = pe.MapNode(interface = fsl.MCFLIRT(), name = 'NodeName_17dcb750', iterfield = ['in_file', 'ref_file'])
NodeHash_17dcb750.inputs.interpolation = 'spline'
NodeHash_17dcb750.inputs.save_mats = True
NodeHash_17dcb750.inputs.save_plots = True
NodeHash_17dcb750.inputs.save_rms = True

#Wraps command **fsl_tsplot**
NodeHash_1a073110 = pe.MapNode(interface = fsl.PlotMotionParams(), name = 'NodeName_1a073110', iterfield = ['in_file'])
NodeHash_1a073110.inputs.args = '-a x,y,z -w 640 -h 144'
NodeHash_1a073110.inputs.in_source = 'fsl'
NodeHash_1a073110.iterables = [('plot_type', ['rotations', 'translations'])]

#Wraps command **fslmaths**
NodeHash_1b2dc9e0 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_1b2dc9e0', iterfield = ['in_file'])
NodeHash_1b2dc9e0.inputs.dimension = 'T'

#Wraps command **bet**
NodeHash_1a0beef0 = pe.MapNode(interface = fsl.BET(), name = 'NodeName_1a0beef0', iterfield = ['in_file'])
NodeHash_1a0beef0.inputs.frac = 0.3
NodeHash_1a0beef0.inputs.mask = True
NodeHash_1a0beef0.inputs.no_output = True

#Wraps command **fslmaths**
NodeHash_1d0ca8e0 = pe.MapNode(interface = fsl.ApplyMask(), name = 'NodeName_1d0ca8e0', iterfield = ['in_file', 'mask_file'])

#Wraps command **fslstats**
NodeHash_1dd3e9f0 = pe.MapNode(interface = fsl.ImageStats(), name = 'NodeName_1dd3e9f0', iterfield = ['in_file'])
NodeHash_1dd3e9f0.inputs.op_string = '-p 98'

#Custom interface wrapping function Tsv2subjectinfo
NodeHash_1d1abaa0 = pe.MapNode(interface = firstlevelhelpers.Tsv2subjectinfo, name = 'NodeName_1d1abaa0', iterfield = ['in_file'])

#Custom interface wrapping function Getpercentthresh
NodeHash_1f4b4700 = pe.MapNode(interface = firstlevelhelpers.Getpercentthresh, name = 'NodeName_1f4b4700', iterfield = ['value'])
NodeHash_1f4b4700.inputs.percentage = 0.75

#Custom interface wrapping function Getpercentthresh
NodeHash_1f4c4010 = pe.MapNode(interface = firstlevelhelpers.Getpercentthresh, name = 'NodeName_1f4c4010', iterfield = ['value'])
NodeHash_1f4c4010.inputs.percentage = 0.1

#Wraps command **fslmaths**
NodeHash_2012a8b0 = pe.MapNode(interface = fsl.Threshold(), name = 'NodeName_2012a8b0', iterfield = ['in_file', 'thresh'])

#Wraps command **fslmaths**
NodeHash_209054a0 = pe.MapNode(interface = fsl.MinImage(), name = 'NodeName_209054a0', iterfield = ['in_file'])
NodeHash_209054a0.inputs.args = '-bin'
NodeHash_209054a0.inputs.dimension = 'T'

#Wraps command **fslmaths**
NodeHash_216bd430 = pe.MapNode(interface = fsl.ChangeDataType(), name = 'NodeName_216bd430', iterfield = ['in_file'])
NodeHash_216bd430.inputs.output_datatype = 'char'

#Wraps command **fslmaths**
NodeHash_2215cce0 = pe.MapNode(interface = fsl.DilateImage(), name = 'NodeName_2215cce0', iterfield = ['in_file'])
NodeHash_2215cce0.inputs.operation = 'max'

#Wraps command **fslstats**
NodeHash_22e25780 = pe.MapNode(interface = fsl.ImageStats(), name = 'NodeName_22e25780', iterfield = ['in_file', 'mask_file'])
NodeHash_22e25780.inputs.op_string = '-p 50'

#Wraps command **fslmaths**
NodeHash_22bc6d90 = pe.MapNode(interface = fsl.ApplyMask(), name = 'NodeName_22bc6d90', iterfield = ['in_file', 'mask_file'])

#Wraps command **fslmaths**
NodeHash_242f4120 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_242f4120', iterfield = ['in_file'])

#Custom interface wrapping function Getusan
NodeHash_24378c70 = pe.MapNode(interface = firstlevelhelpers.Getusan, name = 'NodeName_24378c70', iterfield = ['brightness_thresh', 'in_file'])

#Wraps command **susan**
NodeHash_252a67b0 = pe.MapNode(interface = fsl.SUSAN(), name = 'NodeName_252a67b0', iterfield = ['brightness_threshold', 'in_file', 'usans'])
NodeHash_252a67b0.inputs.dimension = 3
NodeHash_252a67b0.inputs.fwhm = 5
NodeHash_252a67b0.inputs.use_median = 1

#Wraps command **fslmaths**
NodeHash_25b5e480 = pe.MapNode(interface = fsl.ApplyMask(), name = 'NodeName_25b5e480', iterfield = ['in_file', 'mask_file'])

#Custom interface wrapping function Getinormscale
NodeHash_25ccb940 = pe.MapNode(interface = firstlevelhelpers.Getinormscale, name = 'NodeName_25ccb940', iterfield = ['medianval'])

#Wraps command **fslmaths**
NodeHash_26650350 = pe.MapNode(interface = fsl.BinaryMaths(), name = 'NodeName_26650350', iterfield = ['in_file', 'operand_value'])
NodeHash_26650350.inputs.operation = 'mul'

#Wraps command **fslmaths**
NodeHash_25bd3a60 = pe.MapNode(interface = fsl.TemporalFilter(), name = 'NodeName_25bd3a60', iterfield = ['in_file'])
NodeHash_25bd3a60.inputs.highpass_sigma = 25

#Wraps command **fslmaths**
NodeHash_274a4650 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_274a4650', iterfield = ['in_file'])
NodeHash_274a4650.inputs.dimension = 'T'

#Wraps command **fslmaths**
NodeHash_163d1fd0 = pe.MapNode(interface = fsl.BinaryMaths(), name = 'NodeName_163d1fd0', iterfield = ['in_file', 'operand_file'])
NodeHash_163d1fd0.inputs.operation = 'add'

#Makes a model specification compatible with spm/fsl designers.
NodeHash_2a3d5e00 = pe.MapNode(interface = modelgen.SpecifyModel(), name = 'NodeName_2a3d5e00', iterfield = ['functional_runs', 'subject_info'])
NodeHash_2a3d5e00.inputs.high_pass_filter_cutoff = 0
NodeHash_2a3d5e00.inputs.input_units = 'secs'
NodeHash_2a3d5e00.inputs.time_repetition = 2.0

#Generate FEAT specific files
NodeHash_29833a90 = pe.MapNode(interface = fsl.Level1Design(), name = 'NodeName_29833a90', iterfield = ['session_info'])
NodeHash_29833a90.inputs.bases = {'dgamma':{'derivs': False}}
NodeHash_29833a90.inputs.contrasts = [('con-incon', 'T', ['congruent_correct', 'congruent_correct'], [-1, 1])]
NodeHash_29833a90.inputs.interscan_interval = 2.0
NodeHash_29833a90.inputs.model_serial_correlations = True

#Wraps command **feat_model**
NodeHash_2aebc370 = pe.MapNode(interface = fsl.FEATModel(), name = 'NodeName_2aebc370', iterfield = ['ev_files', 'fsf_file'])

#Wraps command **film_gls**
NodeHash_2b6d1970 = pe.MapNode(interface = fsl.FILMGLS(), name = 'NodeName_2b6d1970', iterfield = ['design_file', 'in_file', 'tcon_file'])

#Wraps command **fslmaths**
NodeHash_2c1e4470 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_2c1e4470', iterfield = ['in_file'])
NodeHash_2c1e4470.inputs.dimension = 'T'

#Generic datasink module to store structured outputs
NodeHash_2da13040 = pe.Node(interface = io.DataSink(), name = 'NodeName_2da13040')
NodeHash_2da13040.inputs.base_directory = '/tmp/FIRSTLEVEL'

#Basic interface class to select specific elements from a list
NodeHash_2c23f400 = pe.MapNode(interface = utility.Select(), name = 'NodeName_2c23f400', iterfield = ['inlist'])
NodeHash_2c23f400.inputs.index = 0

#Basic interface class to select specific elements from a list
NodeHash_2f03da90 = pe.MapNode(interface = utility.Select(), name = 'NodeName_2f03da90', iterfield = ['inlist'])
NodeHash_2f03da90.inputs.index = 0

#Wraps command **applywarp**
NodeHash_2f9ab460 = pe.MapNode(interface = fsl.ApplyWarp(), name = 'NodeName_2f9ab460', iterfield = ['field_file', 'in_file', 'premat'])
NodeHash_2f9ab460.inputs.interp = 'trilinear'

#Wraps command **applywarp**
NodeHash_2e98a7b0 = pe.MapNode(interface = fsl.ApplyWarp(), name = 'NodeName_2e98a7b0', iterfield = ['field_file', 'in_file', 'premat'])
NodeHash_2e98a7b0.inputs.interp = 'trilinear'

#Wraps command **fslmerge**
NodeHash_30d4b880 = pe.Node(interface = fsl.Merge(), name = 'NodeName_30d4b880')
NodeHash_30d4b880.inputs.dimension = 't'

#Wraps command **fslmerge**
NodeHash_3183db20 = pe.Node(interface = fsl.Merge(), name = 'NodeName_3183db20')
NodeHash_3183db20.inputs.dimension = 't'

#Generate subject specific second level model
NodeHash_32e34d70 = pe.Node(interface = fsl.L2Model(), name = 'NodeName_32e34d70')
NodeHash_32e34d70.inputs.num_copes = 20

#Wraps command **flameo**
NodeHash_3312ca90 = pe.Node(interface = fsl.FLAMEO(), name = 'NodeName_3312ca90')
NodeHash_3312ca90.inputs.run_mode = 'flame1'

#Wraps command **smoothest**
NodeHash_339d0440 = pe.Node(interface = fsl.SmoothEstimate(), name = 'NodeName_339d0440')

#Wraps command **cluster**
NodeHash_34cc0ba0 = pe.Node(interface = fsl.Cluster(), name = 'NodeName_34cc0ba0')
NodeHash_34cc0ba0.inputs.pthreshold = 0.05
NodeHash_34cc0ba0.inputs.threshold = 2.3

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_339d0440, 'volume', NodeHash_34cc0ba0, 'volume')
analysisflow.connect(NodeHash_339d0440, 'dlh', NodeHash_34cc0ba0, 'dlh')
analysisflow.connect(NodeHash_30d4b880, 'merged_file', NodeHash_34cc0ba0, 'cope_file')
analysisflow.connect(NodeHash_3312ca90, 'zstats', NodeHash_34cc0ba0, 'in_file')
analysisflow.connect(NodeHash_32e34d70, 'design_con', NodeHash_3312ca90, 't_con_file')
analysisflow.connect(NodeHash_32e34d70, 'design_grp', NodeHash_3312ca90, 'cov_split_file')
analysisflow.connect(NodeHash_32e34d70, 'design_mat', NodeHash_3312ca90, 'design_file')
analysisflow.connect(NodeHash_3312ca90, 'res4d', NodeHash_339d0440, 'residual_fit_file')
analysisflow.connect(NodeHash_416fbf0, 'MNI_mask', NodeHash_339d0440, 'mask_file')
analysisflow.connect(NodeHash_3312ca90, 'tdof', NodeHash_339d0440, 'dof')
analysisflow.connect(NodeHash_3183db20, 'merged_file', NodeHash_3312ca90, 'var_cope_file')
analysisflow.connect(NodeHash_2f03da90, 'out', NodeHash_2e98a7b0, 'in_file')
analysisflow.connect(NodeHash_416fbf0, 'MNI_mask', NodeHash_3312ca90, 'mask_file')
analysisflow.connect(NodeHash_30d4b880, 'merged_file', NodeHash_3312ca90, 'cope_file')
analysisflow.connect(NodeHash_2e98a7b0, 'out_file', NodeHash_3183db20, 'in_files')
analysisflow.connect(NodeHash_2f9ab460, 'out_file', NodeHash_30d4b880, 'in_files')
analysisflow.connect(NodeHash_169ead00, 'out_file', NodeHash_2e98a7b0, 'premat')
analysisflow.connect(NodeHash_169ead00, 'out_file', NodeHash_2f9ab460, 'premat')
analysisflow.connect(NodeHash_2c23f400, 'out', NodeHash_2f9ab460, 'in_file')
analysisflow.connect(NodeHash_416fbf0, 'MNI_brain', NodeHash_2e98a7b0, 'ref_file')
analysisflow.connect(NodeHash_416fbf0, 'MNI_brain', NodeHash_2f9ab460, 'ref_file')
analysisflow.connect(NodeHash_2b6d1970, 'copes', NodeHash_2c23f400, 'inlist')
analysisflow.connect(NodeHash_2b6d1970, 'varcopes', NodeHash_2f03da90, 'inlist')
analysisflow.connect(NodeHash_1dd3e9f0, 'out_stat', NodeHash_1f4b4700, 'value')
analysisflow.connect(NodeHash_25ccb940, 'value', NodeHash_26650350, 'operand_value')
analysisflow.connect(NodeHash_242f4120, 'out_file', NodeHash_24378c70, 'in_file')
analysisflow.connect(NodeHash_1dd3e9f0, 'out_stat', NodeHash_1f4c4010, 'value')
analysisflow.connect(NodeHash_1f4c4010, 'out_val', NodeHash_2012a8b0, 'thresh')
analysisflow.connect(NodeHash_24378c70, 'usan', NodeHash_252a67b0, 'usans')
analysisflow.connect(NodeHash_1f4b4700, 'out_val', NodeHash_24378c70, 'brightness_thresh')
analysisflow.connect(NodeHash_1f4b4700, 'out_val', NodeHash_252a67b0, 'brightness_threshold')
analysisflow.connect(NodeHash_22e25780, 'out_stat', NodeHash_25ccb940, 'medianval')
analysisflow.connect(NodeHash_1d1abaa0, 'subject_info', NodeHash_2a3d5e00, 'subject_info')
analysisflow.connect(NodeHash_33a30f0, 'events', NodeHash_1d1abaa0, 'in_file')
analysisflow.connect(NodeHash_559ee70, 'out_file', NodeHash_65ebc70, 'in_files')
analysisflow.connect(NodeHash_65ebc70, 'partial_volume_files', NodeHash_9765120, 'inlist')
analysisflow.connect(NodeHash_9765120, 'out', NodeHash_8541900, 'in_file')
analysisflow.connect(NodeHash_8541900, 'out_file', NodeHash_fa474b0, 'wm_seg')
analysisflow.connect(NodeHash_559ee70, 'out_file', NodeHash_eb37a70, 'reference')
analysisflow.connect(NodeHash_eb37a70, 'out_matrix_file', NodeHash_fa474b0, 'in_matrix_file')
analysisflow.connect(NodeHash_559ee70, 'out_file', NodeHash_a538a30, 'in_file')
analysisflow.connect(NodeHash_416fbf0, 'MNI_brain', NodeHash_a538a30, 'reference')
analysisflow.connect(NodeHash_a538a30, 'out_matrix_file', NodeHash_169ead00, 'in_file2')
analysisflow.connect(NodeHash_fa474b0, 'out_matrix_file', NodeHash_169ead00, 'in_file')
analysisflow.connect(NodeHash_caf1be0, 'roi_file', NodeHash_17dcb750, 'ref_file')
analysisflow.connect(NodeHash_caf1be0, 'roi_file', NodeHash_eb37a70, 'in_file')
analysisflow.connect(NodeHash_17dcb750, 'par_file', NodeHash_1a073110, 'in_file')
analysisflow.connect(NodeHash_17dcb750, 'out_file', NodeHash_1b2dc9e0, 'in_file')
analysisflow.connect(NodeHash_1b2dc9e0, 'out_file', NodeHash_1a0beef0, 'in_file')
analysisflow.connect(NodeHash_1a0beef0, 'mask_file', NodeHash_1d0ca8e0, 'mask_file')
analysisflow.connect(NodeHash_17dcb750, 'out_file', NodeHash_1d0ca8e0, 'in_file')
analysisflow.connect(NodeHash_1d0ca8e0, 'out_file', NodeHash_1dd3e9f0, 'in_file')
analysisflow.connect(NodeHash_2012a8b0, 'out_file', NodeHash_209054a0, 'in_file')
analysisflow.connect(NodeHash_209054a0, 'out_file', NodeHash_216bd430, 'in_file')
analysisflow.connect(NodeHash_216bd430, 'out_file', NodeHash_22e25780, 'mask_file')
analysisflow.connect(NodeHash_216bd430, 'out_file', NodeHash_2215cce0, 'in_file')
analysisflow.connect(NodeHash_1d0ca8e0, 'out_file', NodeHash_2012a8b0, 'in_file')
analysisflow.connect(NodeHash_17dcb750, 'out_file', NodeHash_22e25780, 'in_file')
analysisflow.connect(NodeHash_17dcb750, 'out_file', NodeHash_22bc6d90, 'in_file')
analysisflow.connect(NodeHash_2215cce0, 'out_file', NodeHash_22bc6d90, 'mask_file')
analysisflow.connect(NodeHash_22bc6d90, 'out_file', NodeHash_242f4120, 'in_file')
analysisflow.connect(NodeHash_22bc6d90, 'out_file', NodeHash_252a67b0, 'in_file')
analysisflow.connect(NodeHash_252a67b0, 'smoothed_file', NodeHash_25b5e480, 'in_file')
analysisflow.connect(NodeHash_2215cce0, 'out_file', NodeHash_25b5e480, 'mask_file')
analysisflow.connect(NodeHash_25b5e480, 'out_file', NodeHash_26650350, 'in_file')
analysisflow.connect(NodeHash_26650350, 'out_file', NodeHash_274a4650, 'in_file')
analysisflow.connect(NodeHash_26650350, 'out_file', NodeHash_25bd3a60, 'in_file')
analysisflow.connect(NodeHash_25bd3a60, 'out_file', NodeHash_163d1fd0, 'in_file')
analysisflow.connect(NodeHash_274a4650, 'out_file', NodeHash_163d1fd0, 'operand_file')
analysisflow.connect(NodeHash_163d1fd0, 'out_file', NodeHash_2c1e4470, 'in_file')
analysisflow.connect(NodeHash_163d1fd0, 'out_file', NodeHash_2a3d5e00, 'functional_runs')
analysisflow.connect(NodeHash_2a3d5e00, 'session_info', NodeHash_29833a90, 'session_info')
analysisflow.connect(NodeHash_29833a90, 'fsf_files', NodeHash_2aebc370, 'fsf_file')
analysisflow.connect(NodeHash_29833a90, 'ev_files', NodeHash_2aebc370, 'ev_files')
analysisflow.connect(NodeHash_2aebc370, 'con_file', NodeHash_2b6d1970, 'tcon_file')
analysisflow.connect(NodeHash_2aebc370, 'design_file', NodeHash_2b6d1970, 'design_file')
analysisflow.connect(NodeHash_163d1fd0, 'out_file', NodeHash_2b6d1970, 'in_file')
analysisflow.connect(NodeHash_2b6d1970, 'results_dir', NodeHash_2da13040, 'firstlevel')
analysisflow.connect(NodeHash_2f2a810, 'sub_id', NodeHash_33a30f0, 'sub_id')
analysisflow.connect(NodeHash_33a30f0, 'anat', NodeHash_559ee70, 'in_file')
analysisflow.connect(NodeHash_33a30f0, 'anat', NodeHash_fa474b0, 'reference')
analysisflow.connect(NodeHash_33a30f0, 'func', NodeHash_caf1be0, 'in_file')
analysisflow.connect(NodeHash_33a30f0, 'func', NodeHash_17dcb750, 'in_file')
analysisflow.connect(NodeHash_caf1be0, 'roi_file', NodeHash_fa474b0, 'in_file')
analysisflow.connect(NodeHash_416fbf0, 'MNI_mask', NodeHash_12fba730, 'refmask_file')
analysisflow.connect(NodeHash_416fbf0, 'MNI_head', NodeHash_12fba730, 'ref_file')
analysisflow.connect(NodeHash_a538a30, 'out_matrix_file', NodeHash_12fba730, 'affine_file')
analysisflow.connect(NodeHash_33a30f0, 'anat', NodeHash_12fba730, 'in_file')
analysisflow.connect(NodeHash_12fba730, 'field_file', NodeHash_2e98a7b0, 'field_file')
analysisflow.connect(NodeHash_12fba730, 'field_file', NodeHash_2f9ab460, 'field_file')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 10} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.base_dir = '/media/lukas/goliath/Porcupine/example_workflows/FEAT_fsl_firstlevel_and_secondlevel'
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
