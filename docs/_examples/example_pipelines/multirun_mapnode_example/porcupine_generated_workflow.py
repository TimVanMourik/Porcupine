#This is a Nipype generator. Warning, here be dragons.
import sys
import nipype
import nipype.pipeline as pe
import nipype.interfaces.utility as utility
import nipype.interfaces.io as io
import nipype.interfaces.afni as afni

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Basic interface class generates identity mappings
NodeHash_24ff4a0 = pe.Node(utility.IdentityInterface(fields=['sub_id','run_id']), name = 'NodeName_24ff4a0')
NodeHash_24ff4a0.inputs.run_id = ['run-1', 'run-2']
NodeHash_24ff4a0.iterables = [('sub_id', ['sub-01', 'sub-02'])]

#Generic datagrabber module that wraps around glob in an
NodeHash_1e88370 = pe.Node(io.S3DataGrabber(infields=['sub_id','run_id'], outfields=['func']), name = 'NodeName_1e88370')
NodeHash_1e88370.inputs.bucket = 'openneuro'
NodeHash_1e88370.inputs.sort_filelist = True
NodeHash_1e88370.inputs.template = '%s/func/%s_task-simon_%s_bold.nii.gz'
NodeHash_1e88370.inputs.anon = True
NodeHash_1e88370.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_1e88370.inputs.local_directory = '/tmp'
NodeHash_1e88370.inputs.template_args = dict(func=[['sub_id', 'sub_id', 'run_id']])

#Wraps command **3dvolreg**
NodeHash_19153b0 = pe.MapNode(interface = afni.Volreg(), name = 'NodeName_19153b0', iterfield = ['in_file'])
NodeHash_19153b0.inputs.outputtype = 'NIFTI_GZ'

#Generic datasink module to store structured outputs
NodeHash_2b96290 = pe.Node(interface = io.DataSink(), name = 'NodeName_2b96290')
NodeHash_2b96290.inputs.base_directory = '/tmp'

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_24ff4a0, 'sub_id', NodeHash_2b96290, 'container')
analysisflow.connect(NodeHash_24ff4a0, 'run_id', NodeHash_1e88370, 'run_id')
analysisflow.connect(NodeHash_24ff4a0, 'sub_id', NodeHash_1e88370, 'sub_id')
analysisflow.connect(NodeHash_1e88370, 'func', NodeHash_19153b0, 'in_file')
analysisflow.connect(NodeHash_19153b0, 'oned_file', NodeHash_2b96290, 'moco.moco_params')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 1} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
