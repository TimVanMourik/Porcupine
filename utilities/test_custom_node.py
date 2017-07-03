from nipype.interfaces.utility import Function
from nipype.pipeline import Node
import json
    
def my_custom_func(in_string, default_arg='!'):
	return "Hello, %s%%" % (in_string, default_arg)

MyCustomNode = Node(interface=Function(input_names=['in_string', 'default_arg'],
									   output_names=['out_string'],
									   function=my_custom_func), name='mycustomnode')

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