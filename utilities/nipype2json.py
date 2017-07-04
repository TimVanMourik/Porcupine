#import os

import json

working_dir = '../Resources/Dictionaries/'
cat_nipype = 'NiPype'

for class_name in ['utility', 'io', 'ants', 'fsl', 'afni', 'spm', 'freesurfer', 'camino', 'mrtrix', 'mne', 'slicer']:

    exec('import nipype.interfaces.' + class_name + ' as ' + class_name)
    class_list = [e for e in eval('dir(' + class_name + ')') if e[0].isupper() or e[0].isdigit()]
    op_class_name = class_name.upper()

    nodes = []
    for cls in class_list:
        if eval('"input_spec" in dir(' + class_name + '.' + cls + ')'):
            if cls.endswith('Command'):
                continue

            long_node_title = op_class_name + '.' + cls

            nodename = cls
            all_inputs = eval(class_name+'.'+cls+'.input_spec().traits()').keys()
            all_inputs = [ai for ai in all_inputs if not ai.startswith('trait')]

            try:
                outputs = eval(class_name+'.'+cls+'.output_spec().traits()').keys()
                m_outputs = [ou for ou in outputs if not ou.startswith('trait')]
            except TypeError:
                print('TypeError for outputs')
                m_outputs = []

            try:
                descr = eval(class_name+'.'+cls+'().help(returnhelp=True).splitlines()[0]')
            except: # for Interfaces without valid descriptions
                descr = cls

            titleBlock = {
                            'name': long_node_title,
                            'code': [{  
                                    'language': cat_nipype,
                                    'comment': descr,
                                    'argument': class_name + '.' + cls + '()'
                                    }]
                         }
                    
            ports = []
            input_strings = []
            
            m_inputs = eval(class_name + '.' + cls + '.input_spec().traits(mandatory=True)').keys()
            #par_class = str(eval(class_name + '.' + cls + '.__class__')).split('.')[-2]
            for m_inp in m_inputs:
                codeBlock = {
                        'language': cat_nipype,
                        'argument': m_inp,
                        }
                port = {
                        'input': True,
                        'output': False,
                        'visible': True,
                        'editable': True,
                        'name': m_inp,
                        'code': [codeBlock]
                        }
                ports.append(port);
                            
            m_inputs = set(all_inputs) - set(m_inputs)
            for m_inp in m_inputs:
                codeBlock = {
                        'language': cat_nipype,
                        'argument': m_inp
                        }
                port = {
                        'input': True,
                        'output': False,
                        'visible': False,
                        'editable': False,
                        'name': m_inp,
                        'code': [codeBlock]
                        }
                ports.append(port);

            ## outputs
            output_strings = []
            for m_out in m_outputs:
                codeBlock = {
                        'language': cat_nipype,
                        'argument': m_inp
                        }
                
                port = {
                        'input': False,
                        'output': True,
                        'visible': True,
                        'editable': False,
                        'name': m_out,
                        'code': [codeBlock]
                        }
                ports.append(port);
    			
            #if par_class == op_class_name:
            this_category = [cat_nipype, op_class_name]
            #else:
                #this_category = [cat_nipype, op_class_name, par_class]
                
            node = {
                    'category': this_category,
                    'title': titleBlock,
                    'ports': ports
                    }

            nodes.append(node)

    with open(class_name + '.JSON', 'w') as outfile:
        json.dump({'nodes': nodes}, outfile, sort_keys = False, indent = 2)
    
    
#            opfilename = long_node_title + '.node'
#            with open(os.path.join(working_dir, cat_nipype, opfilename), 'w') as f:
#                f.write(doc.toprettyxml(indent="  "))

# separate code for the Merge Node
#class_name = 'utility'
#exec('import nipype.interfaces.' + class_name + ' as ' + class_name)
#op_class_name = class_name.upper()
#cls = 'Merge'
## outputs first:
#try:
#    outputs = eval(class_name+'.'+cls+'.output_spec().traits()').keys()
#    m_outputs = [ou for ou in outputs if not ou.startswith('trait')]
#except TypeError:
#    print 'TypeError for outputs'
#    m_outputs = []
#
#try:
#    descr = eval(class_name+'.'+cls+'().help(returnhelp=True).splitlines()[0]')
#except: # for Interfaces without valid descriptions
#    descr = cls
#
#for in_nr in range(1,10):
#
#    opfilename = cls + '_%i'%in_nr
#    m_inputs = ['in%i'%i for i in range(1, in_nr+1)]
#    long_node_title = op_class_name+'.'+cls+'.%i'%in_nr
#
#    ## XML stuff
#    ## top-level node
#    node = ET.Element('node')
#    category = ET.SubElement(node, 'category', {'name': cat_nipype})
#    subcat = ET.SubElement(category, 'category', {'name': op_class_name})
#    submergecat = ET.SubElement(subcat, 'category', {'name': cls})
#
#    ## title
#    title = ET.SubElement(node, 'title', {'name': long_node_title})
#    title_code = ET.SubElement(title, 'code')
#    language = ET.SubElement(title_code, 'language', {'name': cat_nipype})
#    comment = ET.SubElement(language, 'comment', {'text': descr})
#    argument = ET.SubElement(language, 'argument', {'name': class_name+'.'+cls+'()'})
#
#    ## inputs
#    input_strings = []
#    for m_inp in m_inputs:
#        input_node = ET.SubElement(node, 'input', {'name': m_inp, 'editable': 'true'})
#        code = ET.SubElement(input_node, 'code')
#        language = ET.SubElement(code, 'language', {'name': cat_nipype})
#        m_input_argument = ET.SubElement(language, 'argument', {'name': m_inp})
#        input_strings.append(ET.tostring(input_node))
#
#    ## outputs
#    output_strings = []
#    for m_out in m_outputs:
#        output_node = ET.SubElement(node, 'output', {'name': m_out, 'editable': 'true'})
#        code = ET.SubElement(output_node, 'code')
#        language = ET.SubElement(code, 'language', {'name': cat_nipype})
#        m_output_argument = ET.SubElement(language, 'argument', {'name': m_out})
#        output_strings.append(ET.tostring(output_node))
#
#
#    doc = minidom.parseString(ET.tostring(node))
#
#    opfilename = long_node_title + '.node'
#    with open(os.path.join(working_dir, cat_nipype, opfilename), 'w') as f:
#        f.write(doc.toprettyxml(indent="  "))
#
#
#        