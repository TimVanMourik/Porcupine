#This is a NiPype generator. Warning, here be dragons.
import nipype
import nipype.pipeline as pe
import nipype.interfaces.utility as utility
import nipype.interfaces.io as io
import nipype.interfaces.fsl as fsl

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Basic interface class generates identity mappings
NodeHash_7b59390 = pe.Node(utility.IdentityInterface(fields=['sub_id']), name = 'NodeName_7b59390')
NodeHash_7b59390.iterables = [('sub_id', ['sub-01', 'sub-02'])]

#Generic datagrabber module that wraps around glob in an
NodeHash_31e5cf0 = pe.Node(interface = io.S3DataGrabber(), name = 'NodeName_31e5cf0')
NodeHash_31e5cf0.inputs.anon = True
NodeHash_31e5cf0.inputs.bucket = 'openneuro'
NodeHash_31e5cf0.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_31e5cf0.inputs.local_directory = '/tmp'
NodeHash_31e5cf0.inputs.sort_filelist = True
NodeHash_31e5cf0.inputs.template = '%s/anat/%s_T1w.nii.gz'
NodeHash_31e5cf0.inputs.template_args = dict(anat=[['sub_id', 'sub_id']])

#Wraps command **bet**
NodeHash_2d87000 = pe.Node(interface = fsl.BET(), name = 'NodeName_2d87000')

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_31e5cf0, 'anat', NodeHash_2d87000, 'in_file')
analysisflow.connect(NodeHash_7b59390, 'sub_id', NodeHash_31e5cf0, 'sub_id')

#Run the workflow
analysisflow.run()
