import json
from nipype2json import node2json
import os.path as op
from importlib import import_module

def filter_nodes(node_list):

    node_list = [n for n in node_list if hasattr(n, '__name__')
                 and not n.__name__.endswith('Command')
                 and n.__name__ not in NODES_TO_EXCLUDE
                 and hasattr(n, 'input_spec')]

    return node_list

category = 'Nipype'
working_dir = op.join(op.dirname(op.dirname(__file__)),
                      'resources', 'dictionaries', category)

MODULES_TO_PARSE = ['utility', 'io', 'ants', 'fsl', 'afni', 'spm',
                    'freesurfer', 'camino', 'mrtrix', 'mne', 'slicer']
MODULES_TO_PARSE = ['interfaces.' + m for m in MODULES_TO_PARSE]
MODULES_TO_PARSE.extend(['algorithms.' + m for m in ['confounds', 'icc', 'mesh', 'metrics',
                                                     'misc', 'modelgen', 'rapidart']])

NODES_TO_EXCLUDE = ['BaseInterface', 'IOBase']

for class_name in MODULES_TO_PARSE:
    module = import_module("nipype.%s" % class_name)
    module_name = module.__name__
    print("Processing module: %s" % module_name)

    node_list = [getattr(module, n) for n in dir(module)
                 if n[0].isupper() or n[0].isdigit()]
    node_list = filter_nodes(node_list)

    nodes_to_save = [node2json(node, module=class_name, custom_node=False, category=category)
                     for node in node_list]

    with open(op.join(working_dir, class_name.split('.')[1] + '.JSON'), 'w') as outfile:
        json.dump({'nodes': nodes_to_save}, outfile, sort_keys=False, indent=2)
