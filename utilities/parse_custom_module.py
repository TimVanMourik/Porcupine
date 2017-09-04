from __future__ import print_function
import sys
import inspect
import importlib
import os.path as op
import json
from nipype2json import node2json
from nipype.interfaces.utility import Function


def custommodule2json(module_path, verbose, add_path):

    sys.path.append(op.dirname(module_path))
    module_to_import = op.basename(module_path).replace('.py', '')
    module = importlib.import_module(module_to_import)
    module_name = module.__name__
    print("Parsing custom module %s ..." % module_name)

    jsons = []
    for node in dir(module):
        node_inst = getattr(module, node)

        if isinstance(node_inst, Function):

            name = str(node)

            if verbose:
                print("Adding node '%s'" % name)

            mpath = module_path if add_path else None
            jsons.append(node2json(node_inst, node_name=name, custom_node=True,
                                   module=module_name, module_path=mpath)
                         )

    outfn = op.abspath(op.join(op.dirname(module_path), module_name + '.JSON'))
    print("Writing nodes to %s ..." % outfn, end='')
    with open(outfn, 'w') as outfile:
        json.dump({'nodes': jsons}, outfile, sort_keys=False, indent=2)
    print(' done.')


if __name__ == '__main__':

    from argparse import ArgumentParser
    parser = ArgumentParser(description='Parse custom modules w/Nipype nodes.')
    parser.add_argument('-m', dest='module', type=str,
                        help="Module to parse")
    parser.add_argument('-v', dest='verbose', action='store_true',
                        help="Print much more output ...")
    parser.add_argument('-a', dest='add_path', action='store_true',
                        help=('Whether to add the absolute path of the module '
                              'to the Nipype-script; if False (default), the '
                              'module is NOT added to the PYTHON_PATH, and '
                              'should thus be located in the directory from '
                              'which the pipeline is run'))
    args = parser.parse_args()
    custommodule2json(args.module, args.verbose, args.add_path)
