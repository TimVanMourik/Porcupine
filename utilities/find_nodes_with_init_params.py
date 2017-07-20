import json
from nipype2json import node2json
import os.path as op
from importlib import import_module
import inspect

category = 'NiPype'
working_dir = op.join(op.dirname(op.dirname(__file__)),
                      'resources', 'dictionaries', category)

MODULES_TO_PARSE = ['utility', 'io', 'ants', 'fsl', 'afni', 'spm',
                    'freesurfer', 'camino', 'mrtrix', 'mne', 'slicer']

NODES_TO_EXCLUDE = ['Function']

for class_name in MODULES_TO_PARSE:
    #print("Class name: %s" % class_name)
    module = import_module("nipype.interfaces.%s" % class_name)
    module_name = module.__name__
    print("Processing module: %s" % module_name)
    node_list = [getattr(module, n) for n in dir(module)
                 if n[0].isupper() or n[0].isdigit()]
    node_list = [n for n in node_list if hasattr(n, '__name__')]
    node_list = [n for n in node_list if not n.__name__.endswith('Command')]
    node_list = [n for n in node_list if n.__name__ not in NODES_TO_EXCLUDE]

    for node in [n for n in node_list if hasattr(n, 'input_spec')]:

        init_argspec = inspect.getfullargspec(node.__init__)
        args, defaults = init_argspec.args, init_argspec.defaults
        defaults = []
        args = [a for a in init_argspec.args if a not in ['self', 'command', 'from_file']]
        
        if args:
            
            if module_name != 'spm':
                try:
                    node_inst = node()
                except (TypeError, ValueError):
                    print(node.__name__)
                    print(args)