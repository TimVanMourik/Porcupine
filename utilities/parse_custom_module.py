from __future__ import print_function
import sys
import inspect
import importlib
import os.path as op
import json
from nipype2json import node2json
from nipype.interfaces.utility import Function


def custommodule2json(module_path, verbose=False):

    sys.path.append(op.dirname(module_path))
    module_to_import = op.basename(module_path).replace('.py', '')
    module = importlib.import_module(module_to_import)
    module_name = module.__name__
    print("Parsing custom module %s ..." % module_name)

    jsons = []
    for node in dir(module):
        
        node_inst = getattr(module, node)
        if isinstance(node_inst, Function):
        
            fstr = node_inst.inputs.function_str
            name = fstr.split(':')[0].split('(')[0].split(' ')[1]

            if verbose:
                print("Adding node '%s'" % name)
            
            jsons.append(node2json(node_inst, custom_node=True,
                                   module=module_name,
                                   category='Custom', module_path=module_path))

    out_fn = op.abspath(op.join(op.dirname(module_path), module_name + '.JSON'))
    print("Writing nodes to %s ..." % out_fn, end='')
    with open(out_fn, 'w') as outfile:
        json.dump({'nodes': jsons}, outfile, sort_keys=False, indent=2)
    print(' done.')

if __name__ == '__main__':

    from argparse import ArgumentParser
    parser = ArgumentParser(description='Parses custom modules with Nipype nodes.')
    parser.add_argument('-m', dest='module', type=str,
                        help="Module to parse")
    parser.add_argument('-v', dest='verbose', action='store_true',
                        help="Print much more output ...")
    
    args = parser.parse_args()
    custommodule2json(args.module, args.verbose)
