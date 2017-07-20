""" nipype2json.py

Makes a Porcupine-compatible dictionary of nodes.
Created by Tomas Knapen (Free University, Amsterdam) &
Lukas Snoek (University of Amsterdam)
"""
import inspect


def node2json(node, module=None, custom_node=False, category="Custom"):
    """ Converts nipype nodes to Porcupine-compatible json-files.

    This function takes a Nipype node from a Python module and
    creates a Porcupine json-file.

    Parameters
    ----------
    node : Nipype Node object
        Nipype node to create a json-dict for.
    module : str
        Name of module in which node is contained.
    custom_node : bool
        Whether the node is a custom node or a node within
        the Nipype package.
    category : str
        Category of node (default: "Custom") 
    """

    if module is None:
        module = "custom"

    if custom_node:
        category = "Custom"

    all_inputs, mandatory_inputs = _get_inputs(node, custom_node)
    all_outputs = _get_outputs(node, custom_node)
    descr = _get_descr(node, custom_node)
    web_url, long_node_title = _get_web_url(node, custom_node)
    node_name = _get_node_name(node, custom_node)

    titleBlock = {'name': '%s.%s' % (module, node_name),
                  'code': [{'language': category,
                            'comment': descr,
                            'web_url': web_url,
                            'argument': module + '.%s()' % node_name}]}

    ports = []

    for inp in all_inputs:
        codeBlock = {'language': category,
                     'argument': inp}
        is_mandatory = inp in mandatory_inputs

        port = {'input': True,
                'output': False,
                'visible': True if is_mandatory else False,
                'editable': True if is_mandatory else False,
                'name': inp,
                'code': [codeBlock]}
        ports.append(port)

    for outp in all_outputs:

        codeBlock = {
            'language': category,
            'argument': outp
        }

        port = {
            'input': False,
            'output': True,
            'visible': True,
            'editable': False,
            'name': outp,
            'code': [codeBlock]
        }
        ports.append(port)

    this_category = [category, module]
    node_to_return = {
        'category': this_category,
        'title': titleBlock,
        'ports': ports
    }
    return node_to_return


def _get_inputs(node, custom_node=True):

    all_inputs, mandatory_inputs = [], []
    if custom_node:
        TO_SKIP = ['function_str', 'trait_added', 'trait_modified',
                   'ignore_exception']
        all_inputs.extend([inp for inp in node.inputs.traits().keys()
                           if not inp in TO_SKIP])
        mandatory_inputs.extend(all_inputs)
    else:
        all_inputs.extend([inp for inp in node.input_spec().traits().keys()
                           if not inp.startswith('trait')])
        mandatory_inputs.extend(node.input_spec().traits(mandatory=True).keys())

    return all_inputs, mandatory_inputs


def _get_outputs(node, custom_node=True):

    if custom_node:
        TO_SKIP = ['trait_added', 'trait_modified']
        if 'return' in node.inputs.function_str:
            all_outputs = [outp for outp in node.outputs.traits().keys()
                           if not outp in TO_SKIP]
        else:
            all_outputs = []
    else:
        if hasattr(node, 'output_spec'):
            if node.output_spec is not None:
                all_outputs = [outp for outp in node.output_spec().traits().keys()
                               if not outp.startswith('trait')]
            else:
                print('No outputs for node %s' % node.__name__)
                all_outputs = []
        else:
            print('No outputs for node %s' % node.__name__)
            all_outputs = []

    return all_outputs


def _get_descr(node, custom_node=True):

    if custom_node:
        descr = node.fullname
    else:
        if hasattr(node, 'help'):
            descr = node.help(returnhelp=True).splitlines()[0]
        else:
            descr = node.__name__

    return descr


def _get_web_url(node, custom_node):

    if custom_node:
        return '', "custom"
    else:
        web_url = 'nipype.readthedocs.io/en/latest/interfaces/generated/interfaces'
        module_tree = inspect.getmodule(node).__name__
        long_node_title = '.'.join([n for n in module_tree.split('.')
                                    if n not in ('interfaces', 'nipype')])
        web_url += '.%s' % long_node_title.split('.')[0]
        if len(long_node_title.split('.')) > 1:
            web_url += '/%s.html' % long_node_title.split('.')[1]
            web_url += '#%s' % node.__name__
        return web_url, long_node_title


def _get_node_name(node, custom_node):

    if custom_node:
        return node.fullname
    else:
        return node.__name__

def pyfunc2json():
    """ Experimental function to convert Python functions
    directly to Porcupine's JSON format (by converting it)
    first to a Nipype node. """
    pass

