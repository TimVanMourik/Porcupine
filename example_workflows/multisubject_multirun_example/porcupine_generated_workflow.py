#This is a Nipype generator. Warning, here be dragons.
import sys
import nipype
import nipype.pipeline as pe
import nipype.interfaces.utility as utility
import nipype.interfaces.io as io
import nipype.interfaces.afni as afni

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Basic interface class generates identity mappings
NodeHash_3a33dd0 = pe.Node(utility.IdentityInterface(fields=['sub_id']), name = 'NodeName_3a33dd0')
NodeHash_3a33dd0.iterables = [('sub_id', ['sub-01', 'sub-02'])]

#Generic datagrabber module that wraps around glob in an
NodeHash_8c0c7e0 = pe.Node(io.S3DataGrabber(infields=['sub_id','run_id'], outfields=['func']), name = 'NodeName_8c0c7e0')
NodeHash_8c0c7e0.inputs.bucket = 'openneuro'
NodeHash_8c0c7e0.inputs.sort_filelist = True
NodeHash_8c0c7e0.inputs.template = '%s/func/%s_task-simon_run-%i_bold.nii.gz'
NodeHash_8c0c7e0.inputs.anon = True
NodeHash_8c0c7e0.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_8c0c7e0.inputs.local_directory = '/tmp'
NodeHash_8c0c7e0.inputs.template_args = dict(func=[['sub_id', 'sub_id', 'run_id']])
NodeHash_8c0c7e0.inputs.run_id = [1, 2]

#Wraps command **3dvolreg**
NodeHash_8c7cd20 = pe.MapNode(interface = afni.Volreg(), name = 'NodeName_8c7cd20', iterfield = ['in_file'])
NodeHash_8c7cd20.inputs.outputtype = 'NIFTI_GZ'

#Generic datasink module to store structured outputs
NodeHash_8c0ce40 = pe.Node(interface = io.DataSink(), name = 'NodeName_8c0ce40')
NodeHash_8c0ce40.inputs.base_directory = '/tmp'

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_8c7cd20, 'oned_file', NodeHash_8c0ce40, 'moco.moco_params')
analysisflow.connect(NodeHash_8c7cd20, 'out_file', NodeHash_8c0ce40, 'moco')
analysisflow.connect(NodeHash_3a33dd0, 'sub_id', NodeHash_8c0ce40, 'container')
analysisflow.connect(NodeHash_8c0c7e0, 'func', NodeHash_8c7cd20, 'in_file')
analysisflow.connect(NodeHash_3a33dd0, 'sub_id', NodeHash_8c0c7e0, 'sub_id')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 1} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
