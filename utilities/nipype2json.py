""" nipype2json.py

Makes a Porcupine-compatible dictionary of nodes.
Created by Tomas Knapen (Free University, Amsterdam) &
Lukas Snoek (University of Amsterdam)
"""

def node2json(node, custom_node=True, mod_name="custom_stuff", category="Custom"):
    
    all_inputs, mandatory_inputs = _get_inputs(node, custom_node)
    all_outputs = _get_outputs(node, custom_node)
    descr = _get_descr(node, custom_node)
    web_url = _get_web_url(node, custom_node)
    node_name = _get_node_name(node, custom_node)

    titleBlock = {'name': long_node_title + '.%s' % node.__name__,
                  'code': [{'language': cat_nipype,
                            'comment': descr,
                            'web_url': web_url,
                            'argument': class_name + '.%s()' % node_name}]}

    ports = []

    for inp in all_inputs:
        codeBlock = {'language': category,
                     'argument': 'inputs.%s' % inp}
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
                'argument': 'outputs.%s' % outp
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
                
    this_category = [category, mod_name]
    node_to_return = {
            'category': this_category,
            'title': titleBlock,
            'ports': ports
            }
    return node_to_return

def _get_inputs(node, custom_node=True):

    if custom_node:
        TO_SKIP = ['function_str', 'trait_added', 'trait_modified',
                   'ignore_exception']
        all_inputs = [inp for inp in node.inputs.traits().keys()
                      if not inp in TO_SKIP]
        mandatory_inputs = all_inputs
    else:
        all_inputs = [inp for inp in node.input_spec().traits().keys()
                      if not inp.startswith('trait')]
        mandatory_inputs = node.input_spec().traits(mandatory=True).keys()
    return all_inputs, mandatory_inputs


def _get_outputs(node, custom_node=True):

    if custom_node:
        TO_SKIP = ['trait_added', 'trait_modified', 'out']
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
        return ''
    else:
        web_url = 'nipype.readthedocs.io/en/latest/interfaces/generated/interfaces'
        module_tree = inspect.getmodule(node).__name__
        long_node_title = '.'.join([n for n in module_tree.split('.')
                                    if n not in ('interfaces', 'nipype')])
        web_url += '.%s' % long_node_title.split('.')[0]
        if len(long_node_title.split('.')) > 1:
            web_url += '/%s.html' % long_node_title.split('.')[1] 
            web_url += '#%s' % node.__name__
        return web_url

def _get_node_name(node, custom_node):

    if custom_node:
        return node.fullname
    else:
        return node.__name__

if __name__ == '__main__':
    from test_custom_node import node2json
    import inspect
    import os.path as op
    from importlib import import_module

    cat_nipype = 'NiPype'
    working_dir = op.join(op.dirname(op.dirname(__file__)),
                          'resources', 'dictionaries', cat_nipype)

    MODULES_TO_PARSE = ['utility', 'io', 'ants', 'fsl', 'afni', 'spm',
                        'freesurfer', 'camino', 'mrtrix', 'mne', 'slicer']
    TO_SKIP = ['Str', 'TraitedSpec', 'Undefined']

    for class_name in MODULES_TO_PARSE[3:4]:
        print("Class name: %s" % class_name)
        module = import_module("nipype.interfaces.%s" % class_name)
        module_name = module.__name__
        node_list = [getattr(module, n) for n in dir(module)
                     if n[0].isupper() or n[0].isdigit()]
        node_list = [n for n in node_list if hasattr(n, '__name__')]
        node_list = [n for n in node_list if not n.__name__.endswith('Command')]
    
        nodes_to_save = [node2json(node, custom_node=False) for node in node_list
                         if hasattr(node, 'input_spec')]

        with open(op.join(working_dir, class_name + '.JSONX'), 'w') as outfile:
            json.dump({'nodes': nodes_to_save}, outfile, sort_keys=False, indent=2)
