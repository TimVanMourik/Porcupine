import json
from nipype2json import node2json
import os.path as op
from importlib import import_module

category = 'NiPype'
working_dir = op.join(op.dirname(op.dirname(__file__)),
                      'resources', 'dictionaries', category)

MODULES_TO_PARSE = ['utility', 'io', 'ants', 'fsl', 'afni', 'spm',
                    'freesurfer', 'camino', 'mrtrix', 'mne', 'slicer']

NODES_TO_EXCLUDE = []

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

    nodes_to_save = [node2json(node, custom_node=False,
                     module_type='interfaces',
                     module=class_name, category=category)
                     for node in node_list
                     if hasattr(node, 'input_spec')]

    with open(op.join(working_dir, class_name + '.JSON'), 'w') as outfile:
        json.dump({'nodes': nodes_to_save}, outfile, sort_keys=False, indent=2)

# nipype has some extra modules which are not "interfaces"
# Start with algorithms

EXTRA_MODULES = ['confounds', 'icc', 'mesh', 'metrics', 'misc', 'modelgen',
                 'rapidart']

for class_name in EXTRA_MODULES:
    module = import_module("nipype.algorithms.%s" % class_name)
    module_name = module.__name__
    print("Processing module: %s" % module_name)
    node_list = [getattr(module, n) for n in dir(module)
                 if n[0].isupper() or n[0].isdigit()]
    node_list = [n for n in node_list if hasattr(n, '__name__')]
    node_list = [n for n in node_list if not n.__name__.endswith('Command')]
    node_list = [n for n in node_list if n.__name__ not in NODES_TO_EXCLUDE]

    nodes_to_save = [node2json(node, custom_node=False,
                     module_type='algorithms',
                     module=class_name, category=category)
                     for node in node_list
                     if hasattr(node, 'input_spec')]
    with open(op.join(working_dir, class_name + '.JSON'), 'w') as outfile:
        json.dump({'nodes': nodes_to_save}, outfile, sort_keys=False, indent=2)