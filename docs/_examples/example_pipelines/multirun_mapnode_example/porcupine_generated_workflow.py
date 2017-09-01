#This is a Nipype generator. Warning, here be dragons.
import sys
import nipype
import nipype.pipeline as pe
import nipype.interfaces.utility as utility
import nipype.interfaces.io as io
import nipype.interfaces.afni as afni

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Basic interface class generates identity mappings
NodeHash_1abe0a0 = pe.Node(utility.IdentityInterface(fields=['sub_id','run_id']), name = 'NodeName_1abe0a0')
NodeHash_1abe0a0.inputs.run_id = ['run-1', 'run-2']
NodeHash_1abe0a0.iterables = [('sub_id', ['sub-01', 'sub-02'])]

#Generic datagrabber module that wraps around glob in an
NodeHash_30575a0 = pe.Node(io.S3DataGrabber(infields=['sub_id','run_id'], outfields=['func']), name = 'NodeName_30575a0')
NodeHash_30575a0.inputs.bucket = 'openneuro'
NodeHash_30575a0.inputs.sort_filelist = True
NodeHash_30575a0.inputs.template = '%s/func/%s_task-simon_%s_bold.nii.gz'
NodeHash_30575a0.inputs.anon = True
NodeHash_30575a0.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_30575a0.inputs.local_directory = '/tmp'
NodeHash_30575a0.inputs.template_args = dict(func=[['sub_id', 'sub_id', 'run_id']])

#Wraps command **3dvolreg**
NodeHash_7757060 = pe.MapNode(interface = afni.Volreg(), name = 'NodeName_7757060', iterfield = ['in_file'])
NodeHash_7757060.inputs.outputtype = 'NIFTI_GZ'

#Generic datasink module to store structured outputs
NodeHash_24385f0 = pe.Node(interface = io.DataSink(), name = 'NodeName_24385f0')
NodeHash_24385f0.inputs.base_directory = '/tmp'

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_1abe0a0, 'run_id', NodeHash_30575a0, 'run_id')
analysisflow.connect(NodeHash_30575a0, 'func', NodeHash_7757060, 'in_file')
analysisflow.connect(NodeHash_1abe0a0, 'sub_id', NodeHash_30575a0, 'sub_id')
analysisflow.connect(NodeHash_7757060, 'oned_file', NodeHash_24385f0, 'moco.moco_params')
analysisflow.connect(NodeHash_7757060, 'out_file', NodeHash_24385f0, 'moco')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 1} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
