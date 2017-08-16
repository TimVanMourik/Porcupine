#This is a NiPype generator. Warning, here be dragons.
import nipype
import nipype.pipeline as pe
import nipype.interfaces.io as io
import nipype.interfaces.afni as afni
import nipype.algorithms.modelgen as modelgen
import nipype.interfaces.fsl as fsl

import sys
sys.path.append('/media/lukas/goliath/Porcupine/example_workflows/firstlevel')
from events2design import Tsv2subjectinfo
NodeHash_8eb7a30 = pe.Node(Tsv2subjectinfo, name='NodeName_8eb7a30')
WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Generic datagrabber module that wraps around glob in an
NodeHash_2a8a2e0 = pe.Node(io.S3DataGrabber(outfields=['outfiles','func']), name = 'NodeName_2a8a2e0')
NodeHash_2a8a2e0.inputs.anon = True
NodeHash_2a8a2e0.inputs.bucket = 'openneuro'
NodeHash_2a8a2e0.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_2a8a2e0.inputs.local_directory = '/tmp'
NodeHash_2a8a2e0.inputs.sort_filelist = True
NodeHash_2a8a2e0.inputs.template = 'sub-01/func/sub-01_task-simon_run-1_bold.nii.gz'

#Generic datagrabber module that wraps around glob in an
NodeHash_b56db30 = pe.Node(io.S3DataGrabber(outfields=['outfiles','events']), name = 'NodeName_b56db30')
NodeHash_b56db30.inputs.anon = True
NodeHash_b56db30.inputs.bucket = 'openneuro'
NodeHash_b56db30.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_b56db30.inputs.local_directory = '/tmp'
NodeHash_b56db30.inputs.sort_filelist = True
NodeHash_b56db30.inputs.template = 'sub-01/func/sub-01_task-simon_run-1_events.tsv'

#Wraps command **3dvolreg**
NodeHash_2a3d2c0 = pe.Node(interface = afni.Volreg(), name = 'NodeName_2a3d2c0')
NodeHash_2a3d2c0.inputs.outputtype = 'NIFTI_GZ'

#Wraps command **fslmaths**
NodeHash_7b7fb70 = pe.Node(interface = fsl.ImageMaths(), name = 'NodeName_7b7fb70')
NodeHash_7b7fb70.inputs.op_string = '-bptf 50 -1'

#Makes a model specification compatible with spm/fsl designers.
NodeHash_3167ee0 = pe.Node(interface = modelgen.SpecifyModel(), name = 'NodeName_3167ee0')
NodeHash_3167ee0.inputs.input_units = 'secs'
NodeHash_3167ee0.inputs.high_pass_filter_cutoff = 0
NodeHash_3167ee0.inputs.time_repetition = 2.0

#Generate FEAT specific files
NodeHash_8ec0000 = pe.Node(interface = fsl.Level1Design(), name = 'NodeName_8ec0000')
NodeHash_8ec0000.inputs.interscan_interval = 2.0
NodeHash_8ec0000.inputs.bases = {'dgamma':{'derivs': False}}
NodeHash_8ec0000.inputs.model_serial_correlations = True
NodeHash_8ec0000.inputs.contrasts = [('con-incon', 'T', ['congruent_correct', 'congruent_correct'], [-1, 1])]

#Wraps command **feat_model**
NodeHash_742dbe0 = pe.Node(interface = fsl.FEATModel(), name = 'NodeName_742dbe0')

#Wraps command **fslmaths**
NodeHash_4c7bc30 = pe.Node(interface = fsl.MeanImage(), name = 'NodeName_4c7bc30')
NodeHash_4c7bc30.inputs.dimension = 'T'

#Wraps command **fslmaths**
NodeHash_3dc1c00 = pe.Node(interface = fsl.ImageMaths(), name = 'NodeName_3dc1c00')
NodeHash_3dc1c00.inputs.op_string = '-add'
NodeHash_3dc1c00.inputs.suffix = '_hp'

#Wraps command **film_gls**
NodeHash_5178890 = pe.Node(interface = fsl.FILMGLS(), name = 'NodeName_5178890')

#Generic datasink module to store structured outputs
NodeHash_8ed1fd0 = pe.Node(interface = io.DataSink(), name = 'NodeName_8ed1fd0')
NodeHash_8ed1fd0.inputs.base_directory = '/tmp'

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_3dc1c00, 'out_file', NodeHash_5178890, 'in_file')
analysisflow.connect(NodeHash_7b7fb70, 'out_file', NodeHash_3167ee0, 'functional_runs')
analysisflow.connect(NodeHash_7b7fb70, 'out_file', NodeHash_3dc1c00, 'in_file2')
analysisflow.connect(NodeHash_4c7bc30, 'out_file', NodeHash_3dc1c00, 'in_file')
analysisflow.connect(NodeHash_2a3d2c0, 'out_file', NodeHash_4c7bc30, 'in_file')
analysisflow.connect(NodeHash_5178890, 'results_dir', NodeHash_8ed1fd0, 'results')
analysisflow.connect(NodeHash_2a3d2c0, 'out_file', NodeHash_7b7fb70, 'in_file')
analysisflow.connect(NodeHash_742dbe0, 'design_file', NodeHash_5178890, 'design_file')
analysisflow.connect(NodeHash_742dbe0, 'con_file', NodeHash_5178890, 'tcon_file')
analysisflow.connect(NodeHash_742dbe0, 'fcon_file', NodeHash_5178890, 'fcon_file')
analysisflow.connect(NodeHash_8ec0000, 'ev_files', NodeHash_742dbe0, 'ev_files')
analysisflow.connect(NodeHash_8ec0000, 'fsf_files', NodeHash_742dbe0, 'fsf_file')
analysisflow.connect(NodeHash_3167ee0, 'session_info', NodeHash_8ec0000, 'session_info')
analysisflow.connect(NodeHash_8eb7a30, 'subject_info', NodeHash_3167ee0, 'subject_info')
analysisflow.connect(NodeHash_b56db30, 'events', NodeHash_8eb7a30, 'in_file')
analysisflow.connect(NodeHash_2a8a2e0, 'func', NodeHash_2a3d2c0, 'in_file')

#Run the workflow
analysisflow.run()
