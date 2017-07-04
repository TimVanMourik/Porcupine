import sys
import inspect
import importlib
import os.path as op
import json
from nipype2json import node2json


def custommodule2json(module_path):

    sys.path.append(op.dirname(module_path))
    module_to_import = op.basename(module_path).replace('.py', '')
    module = importlib.import_module(module_to_import)
    module_name = module.__name__

    jsons = []
    for node in dir(module):
        node_inst = getattr(module, node)
        node_class = node_inst.__class__
        if str(node_class) == "<class 'nipype.pipeline.engine.nodes.Node'>":
            jsons.append(node2json(node_inst, custom_node=True,
                                   module=module_name,
                                   category='Custom'))

    out_fn = op.join(op.dirname(module_path), module_name + '.JSON')
    with open(out_fn, 'w') as outfile:
        json.dump({'nodes': jsons}, outfile, sort_keys=False, indent=2)


if __name__ == '__main__':

    from argparse import ArgumentParser
    parser = ArgumentParser(description='Parses custom modules with Nipype nodes.')
    parser.add_argument('-m', dest='module', type=str,
                        help="Module to parse")
    parser.parse_args()

    custommodule2json(parser.module)
