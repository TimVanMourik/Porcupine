#This is a Nipype generator. Warning, here be dragons.
import sys
import nipype
import nipype.pipeline as pe
import nipype.interfaces.utility as utility
import nipype.interfaces.io as io
import nipype.interfaces.fsl as fsl

WorkingDirectory = "~/Porcupipelines/ThisStudy"

#Basic interface class generates identity mappings
NodeHash_259c960 = pe.Node(utility.IdentityInterface(fields=['sub_id']), name = 'NodeName_259c960')
NodeHash_259c960.iterables = [('sub_id', ['sub-01', 'sub-02'])]

#Generic datagrabber module that wraps around glob in an
NodeHash_2620c60 = pe.Node(io.S3DataGrabber(infields=['sub_id'], outfields=['anat']), name = 'NodeName_2620c60')
NodeHash_2620c60.inputs.bucket = 'openneuro'
NodeHash_2620c60.inputs.sort_filelist = True
NodeHash_2620c60.inputs.template = '%s/anat/%s_T1w.nii.gz'
NodeHash_2620c60.inputs.anon = True
NodeHash_2620c60.inputs.bucket_path = 'ds000101/ds000101_R2.0.0/uncompressed/'
NodeHash_2620c60.inputs.local_directory = '/tmp'
NodeHash_2620c60.inputs.template_args = dict(anat=[['sub_id', 'sub_id']])

#Wraps command **bet**
NodeHash_76feba0 = pe.Node(interface = fsl.BET(), name = 'NodeName_76feba0')

#Generic datasink module to store structured outputs
NodeHash_244f6f0 = pe.Node(interface = io.DataSink(), name = 'NodeName_244f6f0')

#Create a workflow to connect all those nodes
analysisflow = nipype.Workflow('MyWorkflow')
analysisflow.connect(NodeHash_76feba0, 'out_file', NodeHash_244f6f0, 'BET_results')
analysisflow.connect(NodeHash_259c960, 'sub_id', NodeHash_244f6f0, 'container')
analysisflow.connect(NodeHash_2620c60, 'anat', NodeHash_76feba0, 'in_file')
analysisflow.connect(NodeHash_259c960, 'sub_id', NodeHash_2620c60, 'sub_id')

#Run the workflow
plugin = 'MultiProc' #adjust your desired plugin here
plugin_args = {'n_procs': 1} #adjust to your number of cores
analysisflow.write_graph(graph2use='flat', format='png', simple_form=False)
analysisflow.run(plugin=plugin, plugin_args=plugin_args)
