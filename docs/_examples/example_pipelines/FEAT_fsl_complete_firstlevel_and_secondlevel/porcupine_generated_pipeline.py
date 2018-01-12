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
NodeHash_30ba470 = pe.Node(utility.IdentityInterface(fields=['sub_id']), name = 'NodeName_30ba470')
NodeHash_30ba470.inputs.sub_id = ['sub-02', 'sub-03', 'sub-04', 'sub-05', 'sub-06', 'sub-07', 'sub-08', 'sub-09', 'sub-10', 'sub-11', 'sub-12', 'sub-13', 'sub-14', 'sub-15', 'sub-16', 'sub-17', 'sub-18', 'sub-19', 'sub-20', 'sub-21']

#Generic datagrabber module that wraps around glob in an
NodeHash_34d5650 = pe.MapNode(io.S3DataGrabber(infields=['field_template','sub_id'], outfields=['func','events','anat']), name = 'NodeName_34d5650', iterfield = ['sub_id'])
NodeHash_34d5650.inputs.anon = True
NodeHash_34d5650.inputs.bucket = 'openneuro'
NodeHash_34d5650.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_34d5650.inputs.local_directory = '/tmp'
NodeHash_34d5650.inputs.sort_filelist = True
NodeHash_34d5650.inputs.template = '*'
NodeHash_34d5650.inputs.template_args = dict(func=[['sub_id', 'sub_id']], events=[['sub_id', 'sub_id']], anat=[['sub_id', 'sub_id']])
NodeHash_34d5650.inputs.field_template = dict(func='%s/func/%s_task-simon_run-1_bold.nii.gz', events='%s/func/%s_task-simon_run-1_events.tsv', anat='%s/anat/%s_T1w.nii.gz')

#Wraps command **bet**
NodeHash_3a78af0 = pe.MapNode(interface = fsl.BET(), name = 'NodeName_3a78af0', iterfield = ['in_file'])
NodeHash_3a78af0.inputs.frac = 0.3
NodeHash_3a78af0.inputs.robust = True

#Wraps command **fast**
NodeHash_4910410 = pe.MapNode(interface = fsl.FAST(), name = 'NodeName_4910410', iterfield = ['in_files'])

#Basic interface class to select specific elements from a list
NodeHash_66c11e0 = pe.MapNode(interface = utility.Select(), name = 'NodeName_66c11e0', iterfield = ['inlist'])
NodeHash_66c11e0.inputs.index = 2

#Wraps command **fslmaths**
NodeHash_7506130 = pe.MapNode(interface = fsl.Threshold(), name = 'NodeName_7506130', iterfield = ['in_file'])
NodeHash_7506130.inputs.args = '-bin'
NodeHash_7506130.inputs.thresh = 0.5

#Wraps command **fslroi**
NodeHash_6754090 = pe.MapNode(interface = fsl.ExtractROI(), name = 'NodeName_6754090', iterfield = ['in_file'])
NodeHash_6754090.inputs.t_min = 1
NodeHash_6754090.inputs.t_size = 1

#Wraps command **flirt**
NodeHash_96af430 = pe.MapNode(interface = fsl.FLIRT(), name = 'NodeName_96af430', iterfield = ['in_file', 'reference'])

#Wraps command **flirt**
NodeHash_a9682a0 = pe.MapNode(interface = fsl.FLIRT(), name = 'NodeName_a9682a0', iterfield = ['in_file', 'in_matrix_file', 'reference', 'wm_seg'])
NodeHash_a9682a0.inputs.cost = 'bbr'
NodeHash_a9682a0.inputs.dof = 6
NodeHash_a9682a0.inputs.no_resample = True

#Wraps command **mcflirt**
NodeHash_de46680 = pe.MapNode(interface = fsl.MCFLIRT(), name = 'NodeName_de46680', iterfield = ['in_file', 'ref_file'])
NodeHash_de46680.inputs.interpolation = 'spline'
NodeHash_de46680.inputs.save_mats = True
NodeHash_de46680.inputs.save_plots = True
NodeHash_de46680.inputs.save_rms = True

#Wraps command **fsl_tsplot**
NodeHash_e827000 = pe.MapNode(interface = fsl.PlotMotionParams(), name = 'NodeName_e827000', iterfield = ['in_file'])
NodeHash_e827000.inputs.args = '-a x,y,z -w 640 -h 144'
NodeHash_e827000.inputs.in_source = 'fsl'
NodeHash_e827000.iterables = [('plot_type', ['rotations', 'translations'])]

#Wraps command **fslmaths**
NodeHash_12ef2460 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_12ef2460', iterfield = ['in_file'])
NodeHash_12ef2460.inputs.dimension = 'T'

#Wraps command **bet**
NodeHash_131f40e0 = pe.MapNode(interface = fsl.BET(), name = 'NodeName_131f40e0', iterfield = ['in_file'])
NodeHash_131f40e0.inputs.frac = 0.3
NodeHash_131f40e0.inputs.mask = True
NodeHash_131f40e0.inputs.no_output = True

#Wraps command **fslmaths**
NodeHash_1419ab10 = pe.MapNode(interface = fsl.ApplyMask(), name = 'NodeName_1419ab10', iterfield = ['in_file', 'mask_file'])

#Wraps command **fslstats**
NodeHash_14358ae0 = pe.MapNode(interface = fsl.ImageStats(), name = 'NodeName_14358ae0', iterfield = ['in_file'])
NodeHash_14358ae0.inputs.op_string = '-p 98'

#Custom interface wrapping function Tsv2subjectinfo
NodeHash_1425b530 = pe.MapNode(interface = firstlevelhelpers.Tsv2subjectinfo, name = 'NodeName_1425b530', iterfield = ['in_file'])

#Custom interface wrapping function Getpercentthresh
NodeHash_16852000 = pe.MapNode(interface = firstlevelhelpers.Getpercentthresh, name = 'NodeName_16852000', iterfield = ['value'])
NodeHash_16852000.inputs.percentage = 0.75

#Custom interface wrapping function Getpercentthresh
NodeHash_16878250 = pe.MapNode(interface = firstlevelhelpers.Getpercentthresh, name = 'NodeName_16878250', iterfield = ['value'])
NodeHash_16878250.inputs.percentage = 0.1

#Wraps command **fslmaths**
NodeHash_171fdb30 = pe.MapNode(interface = fsl.Threshold(), name = 'NodeName_171fdb30', iterfield = ['in_file', 'thresh'])

#Wraps command **fslmaths**
NodeHash_179e1da0 = pe.MapNode(interface = fsl.MinImage(), name = 'NodeName_179e1da0', iterfield = ['in_file'])
NodeHash_179e1da0.inputs.args = '-bin'
NodeHash_179e1da0.inputs.dimension = 'T'

#Wraps command **fslmaths**
NodeHash_1879dad0 = pe.MapNode(interface = fsl.ChangeDataType(), name = 'NodeName_1879dad0', iterfield = ['in_file'])
NodeHash_1879dad0.inputs.output_datatype = 'char'

#Wraps command **fslmaths**
NodeHash_188ac400 = pe.MapNode(interface = fsl.DilateImage(), name = 'NodeName_188ac400', iterfield = ['in_file'])
NodeHash_188ac400.inputs.operation = 'max'

#Wraps command **fslstats**
NodeHash_1a202720 = pe.MapNode(interface = fsl.ImageStats(), name = 'NodeName_1a202720', iterfield = ['in_file', 'mask_file'])
NodeHash_1a202720.inputs.op_string = '-p 50'

#Wraps command **fslmaths**
NodeHash_19cad2d0 = pe.MapNode(interface = fsl.ApplyMask(), name = 'NodeName_19cad2d0', iterfield = ['in_file', 'mask_file'])

#Wraps command **fslmaths**
NodeHash_1ba62de0 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_1ba62de0', iterfield = ['in_file'])

#Custom interface wrapping function Getusan
NodeHash_1b45a190 = pe.MapNode(interface = firstlevelhelpers.Getusan, name = 'NodeName_1b45a190', iterfield = ['brightness_thresh', 'in_file'])

#Wraps command **susan**
NodeHash_1be88ee0 = pe.MapNode(interface = fsl.SUSAN(), name = 'NodeName_1be88ee0', iterfield = ['brightness_threshold', 'in_file', 'usans'])
NodeHash_1be88ee0.inputs.dimension = 3
NodeHash_1be88ee0.inputs.fwhm = 5
NodeHash_1be88ee0.inputs.use_median = 1

#Wraps command **fslmaths**
NodeHash_1becb6b0 = pe.MapNode(interface = fsl.ApplyMask(), name = 'NodeName_1becb6b0', iterfield = ['in_file', 'mask_file'])

#Custom interface wrapping function Getinormscale
NodeHash_1dce7160 = pe.MapNode(interface = firstlevelhelpers.Getinormscale, name = 'NodeName_1dce7160', iterfield = ['medianval'])

#Wraps command **fslmaths**
NodeHash_1de5d180 = pe.MapNode(interface = fsl.BinaryMaths(), name = 'NodeName_1de5d180', iterfield = ['in_file', 'operand_value'])
NodeHash_1de5d180.inputs.operation = 'mul'

#Wraps command **fslmaths**
NodeHash_1e98cad0 = pe.MapNode(interface = fsl.TemporalFilter(), name = 'NodeName_1e98cad0', iterfield = ['in_file'])
NodeHash_1e98cad0.inputs.highpass_sigma = 25

#Wraps command **fslmaths**
NodeHash_1e558730 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_1e558730', iterfield = ['in_file'])
NodeHash_1e558730.inputs.dimension = 'T'

#Wraps command **fslmaths**
NodeHash_1fdac460 = pe.MapNode(interface = fsl.BinaryMaths(), name = 'NodeName_1fdac460', iterfield = ['in_file', 'operand_file'])
NodeHash_1fdac460.inputs.operation = 'add'

#Makes a model specification compatible with spm/fsl designers.
NodeHash_214dcae0 = pe.MapNode(interface = modelgen.SpecifyModel(), name = 'NodeName_214dcae0', iterfield = ['functional_runs', 'subject_info'])
NodeHash_214dcae0.inputs.high_pass_filter_cutoff = 0
NodeHash_214dcae0.inputs.input_units = 'secs'
NodeHash_214dcae0.inputs.time_repetition = 2.0

#Generate FEAT specific files
NodeHash_2087a210 = pe.MapNode(interface = fsl.Level1Design(), name = 'NodeName_2087a210', iterfield = ['session_info'])
NodeHash_2087a210.inputs.bases = {'dgamma':{'derivs': False}}
NodeHash_2087a210.inputs.contrasts = [('con-incon', 'T', ['congruent_correct', 'congruent_correct'], [-1, 1])]
NodeHash_2087a210.inputs.interscan_interval = 2.0
NodeHash_2087a210.inputs.model_serial_correlations = True

#Wraps command **feat_model**
NodeHash_219c0190 = pe.MapNode(interface = fsl.FEATModel(), name = 'NodeName_219c0190', iterfield = ['ev_files', 'fsf_file'])

#Wraps command **film_gls**
NodeHash_215cb480 = pe.MapNode(interface = fsl.FILMGLS(), name = 'NodeName_215cb480', iterfield = ['design_file', 'in_file', 'tcon_file'])

#Wraps command **fslmaths**
NodeHash_23b7ddc0 = pe.MapNode(interface = fsl.MeanImage(), name = 'NodeName_23b7ddc0', iterfield = ['in_file'])
NodeHash_23b7ddc0.inputs.dimension = 'T'

#Generic datasink module to store structured outputs
NodeHash_23ed28b0 = pe.Node(interface = io.DataSink(), name = 'NodeName_23ed28b0')
NodeHash_23ed28b0.inputs.base_directory = '/tmp/FIRSTLEVEL'

#Basic interface class to select specific elements from a list
NodeHash_256f1c70 = pe.MapNode(interface = utility.Select(), name = 'NodeName_256f1c70', iterfield = ['inlist'])
NodeHash_256f1c70.inputs.index = 0

#Basic interface class to select specific elements from a list
NodeHash_111366a0 = pe.MapNode(interface = utility.Select(), name = 'NodeName_111366a0', iterfield = ['inlist'])
NodeHash_111366a0.inputs.index = 0

#Generate subject specific second level model
NodeHash_263f71d0 = pe.Node(interface = fsl.L2Model(), name = 'NodeName_263f71d0')
NodeHash_263f71d0.inputs.num_copes = 20

#Custom interface wrapping function Find_fsl_mni_files
NodeHash_26dc8f20 = pe.Node(interface = firstlevelhelpers.Find_fsl_mni_files, name = 'NodeName_26dc8f20')

#Wraps command **flirt**
NodeHash_25be7e50 = pe.MapNode(interface = fsl.FLIRT(), name = 'NodeName_25be7e50', iterfield = ['in_file'])
NodeHash_25be7e50.inputs.cost = 'corratio'
NodeHash_25be7e50.inputs.dof = 12
NodeHash_25be7e50.inputs.no_resample = True
NodeHash_25be7e50.inputs.searchr_x = [-90, 90]
NodeHash_25be7e50.inputs.searchr_y = [-90, 90]
NodeHash_25be7e50.inputs.searchr_z = [-90, 90]

#Wraps command **convert_xfm**
NodeHash_278185d0 = pe.MapNode(interface = fsl.ConvertXFM(), name = 'NodeName_278185d0', iterfield = ['in_file', 'in_file2'])
NodeHash_278185d0.inputs.concat_xfm = True

#Wraps command **fnirt**
NodeHash_29b70700 = pe.MapNode(interface = fsl.FNIRT(), name = 'NodeName_29b70700', iterfield = ['in_file', 'affine_file'])
NodeHash_29b70700.inputs.field_file = True
NodeHash_29b70700.inputs.config_file = 'T1_2_MNI152_2mm'
NodeHash_29b70700.inputs.warp_resolution = (10, 10, 10)

#Wraps command **applywarp**
NodeHash_2b7ae5e0 = pe.MapNode(interface = fsl.ApplyWarp(), name = 'NodeName_2b7ae5e0', iterfield = ['field_file', 'in_file', 'premat'])
NodeHash_2b7ae5e0.inputs.interp = 'trilinear'

#Wraps command **applywarp**
NodeHash_2f7b4860 = pe.MapNode(interface = fsl.ApplyWarp(), name = 'NodeName_2f7b4860', iterfield = ['field_file', 'in_file', 'premat'])
NodeHash_2f7b4860.inputs.interp = 'trilinear'

#Wraps command **fslmerge**
NodeHash_2e8e9e00 = pe.Node(interface = fsl.Merge(), name = 'NodeName_2e8e9e00')
NodeHash_2e8e9e00.inputs.dimension = 't'

#Wraps command **flameo**
NodeHash_313ca880 = pe.Node(interface = fsl.FLAMEO(), name = 'NodeName_313ca880')
NodeHash_313ca880.inputs.run_mode = 'flame1'

#Wraps command **smoothest**
NodeHash_314ce330 = pe.Node(interface = fsl.SmoothEstimate(), name = 'NodeName_314ce330')

#Wraps command **cluster**
NodeHash_332d21c0 = pe.Node(interface = fsl.Cluster(), name = 'NodeName_332d21c0')
NodeHash_332d21c0.inputs.pthreshold = 0.05
NodeHash_332d21c0.inputs.threshold = 2.3

#Wraps command **fslmerge**
NodeHash_33d80690 = pe.Node(interface = fsl.Merge(), name = 'NodeName_33d80690')
NodeHash_33d80690.inputs.dimension = 't'

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_313ca880, 'zstats', NodeHash_314ce330, 'zstat_file')
analysisflow.connect(NodeHash_26dc8f20, 'MNI_brain', NodeHash_2f7b4860, 'ref_file')
analysisflow.connect(NodeHash_26dc8f20, 'MNI_brain', NodeHash_2b7ae5e0, 'ref_file')
analysisflow.connect(NodeHash_26dc8f20, 'MNI_head', NodeHash_29b70700, 'ref_file')
analysisflow.connect(NodeHash_26dc8f20, 'MNI_mask', NodeHash_313ca880, 'mask_file')
analysisflow.connect(NodeHash_26dc8f20, 'MNI_mask', NodeHash_314ce330, 'mask_file')
analysisflow.connect(NodeHash_26dc8f20, 'MNI_mask', NodeHash_29b70700, 'refmask_file')
analysisflow.connect(NodeHash_26dc8f20, 'MNI_brain', NodeHash_25be7e50, 'reference')
analysisflow.connect(NodeHash_29b70700, 'field_file', NodeHash_2f7b4860, 'field_file')
analysisflow.connect(NodeHash_29b70700, 'field_file', NodeHash_2b7ae5e0, 'field_file')
analysisflow.connect(NodeHash_25be7e50, 'out_matrix_file', NodeHash_29b70700, 'affine_file')
analysisflow.connect(NodeHash_6754090, 'roi_file', NodeHash_a9682a0, 'in_file')
analysisflow.connect(NodeHash_215cb480, 'results_dir', NodeHash_23ed28b0, 'firstlevel')
analysisflow.connect(NodeHash_1fdac460, 'out_file', NodeHash_215cb480, 'in_file')
analysisflow.connect(NodeHash_219c0190, 'design_file', NodeHash_215cb480, 'design_file')
analysisflow.connect(NodeHash_219c0190, 'con_file', NodeHash_215cb480, 'tcon_file')
analysisflow.connect(NodeHash_2087a210, 'ev_files', NodeHash_219c0190, 'ev_files')
analysisflow.connect(NodeHash_2087a210, 'fsf_files', NodeHash_219c0190, 'fsf_file')
analysisflow.connect(NodeHash_214dcae0, 'session_info', NodeHash_2087a210, 'session_info')
analysisflow.connect(NodeHash_1fdac460, 'out_file', NodeHash_214dcae0, 'functional_runs')
analysisflow.connect(NodeHash_1fdac460, 'out_file', NodeHash_23b7ddc0, 'in_file')
analysisflow.connect(NodeHash_1e558730, 'out_file', NodeHash_1fdac460, 'operand_file')
analysisflow.connect(NodeHash_1e98cad0, 'out_file', NodeHash_1fdac460, 'in_file')
analysisflow.connect(NodeHash_1de5d180, 'out_file', NodeHash_1e98cad0, 'in_file')
analysisflow.connect(NodeHash_1de5d180, 'out_file', NodeHash_1e558730, 'in_file')
analysisflow.connect(NodeHash_1becb6b0, 'out_file', NodeHash_1de5d180, 'in_file')
analysisflow.connect(NodeHash_188ac400, 'out_file', NodeHash_1becb6b0, 'mask_file')
analysisflow.connect(NodeHash_1be88ee0, 'smoothed_file', NodeHash_1becb6b0, 'in_file')
analysisflow.connect(NodeHash_19cad2d0, 'out_file', NodeHash_1be88ee0, 'in_file')
analysisflow.connect(NodeHash_19cad2d0, 'out_file', NodeHash_1ba62de0, 'in_file')
analysisflow.connect(NodeHash_188ac400, 'out_file', NodeHash_19cad2d0, 'mask_file')
analysisflow.connect(NodeHash_de46680, 'out_file', NodeHash_19cad2d0, 'in_file')
analysisflow.connect(NodeHash_de46680, 'out_file', NodeHash_1a202720, 'in_file')
analysisflow.connect(NodeHash_1419ab10, 'out_file', NodeHash_171fdb30, 'in_file')
analysisflow.connect(NodeHash_1879dad0, 'out_file', NodeHash_188ac400, 'in_file')
analysisflow.connect(NodeHash_1879dad0, 'out_file', NodeHash_1a202720, 'mask_file')
analysisflow.connect(NodeHash_179e1da0, 'out_file', NodeHash_1879dad0, 'in_file')
analysisflow.connect(NodeHash_171fdb30, 'out_file', NodeHash_179e1da0, 'in_file')
analysisflow.connect(NodeHash_1419ab10, 'out_file', NodeHash_14358ae0, 'in_file')
analysisflow.connect(NodeHash_de46680, 'out_file', NodeHash_1419ab10, 'in_file')
analysisflow.connect(NodeHash_131f40e0, 'mask_file', NodeHash_1419ab10, 'mask_file')
analysisflow.connect(NodeHash_12ef2460, 'out_file', NodeHash_131f40e0, 'in_file')
analysisflow.connect(NodeHash_de46680, 'out_file', NodeHash_12ef2460, 'in_file')
analysisflow.connect(NodeHash_de46680, 'par_file', NodeHash_e827000, 'in_file')
analysisflow.connect(NodeHash_6754090, 'roi_file', NodeHash_96af430, 'in_file')
analysisflow.connect(NodeHash_6754090, 'roi_file', NodeHash_de46680, 'ref_file')
analysisflow.connect(NodeHash_a9682a0, 'out_matrix_file', NodeHash_278185d0, 'in_file')
analysisflow.connect(NodeHash_25be7e50, 'out_matrix_file', NodeHash_278185d0, 'in_file2')
analysisflow.connect(NodeHash_3a78af0, 'out_file', NodeHash_25be7e50, 'in_file')
analysisflow.connect(NodeHash_96af430, 'out_matrix_file', NodeHash_a9682a0, 'in_matrix_file')
analysisflow.connect(NodeHash_3a78af0, 'out_file', NodeHash_96af430, 'reference')
analysisflow.connect(NodeHash_7506130, 'out_file', NodeHash_a9682a0, 'wm_seg')
analysisflow.connect(NodeHash_66c11e0, 'out', NodeHash_7506130, 'in_file')
analysisflow.connect(NodeHash_4910410, 'partial_volume_files', NodeHash_66c11e0, 'inlist')
analysisflow.connect(NodeHash_3a78af0, 'out_file', NodeHash_4910410, 'in_files')
analysisflow.connect(NodeHash_1425b530, 'subject_info', NodeHash_214dcae0, 'subject_info')
analysisflow.connect(NodeHash_1a202720, 'out_stat', NodeHash_1dce7160, 'medianval')
analysisflow.connect(NodeHash_16852000, 'out_val', NodeHash_1be88ee0, 'brightness_threshold')
analysisflow.connect(NodeHash_16852000, 'out_val', NodeHash_1b45a190, 'brightness_thresh')
analysisflow.connect(NodeHash_1b45a190, 'usan', NodeHash_1be88ee0, 'usans')
analysisflow.connect(NodeHash_16878250, 'out_val', NodeHash_171fdb30, 'thresh')
analysisflow.connect(NodeHash_14358ae0, 'out_stat', NodeHash_16878250, 'value')
analysisflow.connect(NodeHash_1ba62de0, 'out_file', NodeHash_1b45a190, 'in_file')
analysisflow.connect(NodeHash_1dce7160, 'value', NodeHash_1de5d180, 'operand_value')
analysisflow.connect(NodeHash_14358ae0, 'out_stat', NodeHash_16852000, 'value')
analysisflow.connect(NodeHash_215cb480, 'varcopes', NodeHash_111366a0, 'inlist')
analysisflow.connect(NodeHash_215cb480, 'copes', NodeHash_256f1c70, 'inlist')
analysisflow.connect(NodeHash_256f1c70, 'out', NodeHash_2f7b4860, 'in_file')
analysisflow.connect(NodeHash_278185d0, 'out_file', NodeHash_2f7b4860, 'premat')
analysisflow.connect(NodeHash_278185d0, 'out_file', NodeHash_2b7ae5e0, 'premat')
analysisflow.connect(NodeHash_2f7b4860, 'out_file', NodeHash_33d80690, 'in_files')
analysisflow.connect(NodeHash_2b7ae5e0, 'out_file', NodeHash_2e8e9e00, 'in_files')
analysisflow.connect(NodeHash_33d80690, 'merged_file', NodeHash_313ca880, 'cope_file')
analysisflow.connect(NodeHash_111366a0, 'out', NodeHash_2b7ae5e0, 'in_file')
analysisflow.connect(NodeHash_2e8e9e00, 'merged_file', NodeHash_313ca880, 'var_cope_file')
analysisflow.connect(NodeHash_313ca880, 'res4d', NodeHash_314ce330, 'residual_fit_file')
analysisflow.connect(NodeHash_263f71d0, 'design_mat', NodeHash_313ca880, 'design_file')
analysisflow.connect(NodeHash_263f71d0, 'design_grp', NodeHash_313ca880, 'cov_split_file')
analysisflow.connect(NodeHash_263f71d0, 'design_con', NodeHash_313ca880, 't_con_file')
analysisflow.connect(NodeHash_313ca880, 'zstats', NodeHash_332d21c0, 'in_file')
analysisflow.connect(NodeHash_33d80690, 'merged_file', NodeHash_332d21c0, 'cope_file')
analysisflow.connect(NodeHash_314ce330, 'dlh', NodeHash_332d21c0, 'dlh')
analysisflow.connect(NodeHash_314ce330, 'volume', NodeHash_332d21c0, 'volume')
analysisflow.connect(NodeHash_30ba470, 'sub_id', NodeHash_34d5650, 'sub_id')
analysisflow.connect(NodeHash_34d5650, 'func', NodeHash_6754090, 'in_file')
analysisflow.connect(NodeHash_34d5650, 'func', NodeHash_de46680, 'in_file')
analysisflow.connect(NodeHash_34d5650, 'events', NodeHash_1425b530, 'in_file')
analysisflow.connect(NodeHash_34d5650, 'anat', NodeHash_3a78af0, 'in_file')
analysisflow.connect(NodeHash_34d5650, 'anat', NodeHash_a9682a0, 'reference')
analysisflow.connect(NodeHash_34d5650, 'anat', NodeHash_29b70700, 'in_file')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 10} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
