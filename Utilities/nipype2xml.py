import os
import xml.etree.ElementTree as ET
import xml.dom.minidom as minidom

working_dir = '../Resources/Dictionaries/'
# os.chdir(working_dir)
cat_nipype = 'NiPype'

for class_name in ['utility', 'io', 'ants', 'fsl', 'afni', 'spm', 'freesurfer']:

    exec('import nipype.interfaces.' + class_name + ' as ' + class_name)

    class_list = [e for e in eval('dir(' + class_name + ')') if e[0].isupper() or e[0].isdigit()]

    op_class_name = class_name.upper()

    input_output_dict = {}

    for cls in class_list:
        print cls
        if eval('"input_spec" in dir(' + class_name + '.' + cls + ')'):
            ##
            ## this is a node we'll want to write to xml
            ##
            if cls.endswith('Command'):
                continue

            print 'is command'
            long_node_title = op_class_name+'.'+cls
            print long_node_title

            nodename = cls
            all_inputs = eval(class_name+'.'+cls+'.input_spec().traits()').keys()
            all_inputs = [ai for ai in all_inputs if not ai.startswith('trait')]

            m_inputs = eval(class_name+'.'+cls+'.input_spec().traits(mandatory=True)').keys()
            try:
                outputs = eval(class_name+'.'+cls+'.output_spec().traits()').keys()
                m_outputs = [ou for ou in outputs if not ou.startswith('trait')]
            except TypeError:
                print 'TypeError for outputs'
                m_outputs = []

            try:
                descr = eval(class_name+'.'+cls+'().help(returnhelp=True).splitlines()[0]')
            except TypeError: # for Interfaces without valid descriptions
                descr = cls
            except ValueError: # for Interfaces without valid descriptions
                descr = cls

            ## XML stuff
            ## top-level node
            node = ET.Element('node')
            category = ET.SubElement(node, 'category', {'name': cat_nipype})
            subcat = ET.SubElement(category, 'category', {'name': op_class_name})

            ## title
            title = ET.SubElement(node, 'title', {'name': long_node_title})
            title_code = ET.SubElement(title, 'code')
            language = ET.SubElement(title_code, 'language', {'name': cat_nipype})
            comment = ET.SubElement(language, 'comment', {'text': descr})
            argument = ET.SubElement(language, 'argument', {'name': class_name+'.'+cls+'()'})

            ## inputs
            input_strings = []
            for m_inp in m_inputs:
                input_node = ET.SubElement(node, 'input', {'name': m_inp, 'editable': 'false'})
                code = ET.SubElement(input_node, 'code')
                language = ET.SubElement(code, 'language', {'name': cat_nipype})
                m_input_argument = ET.SubElement(language, 'argument', {'name': m_inp})
                input_strings.append(ET.tostring(input_node))

            ## outputs
            output_strings = []
            for m_out in m_outputs:
                output_node = ET.SubElement(node, 'output', {'name': m_out, 'editable': 'false'})
                code = ET.SubElement(output_node, 'code')
                language = ET.SubElement(code, 'language', {'name': cat_nipype})
                m_output_argument = ET.SubElement(language, 'argument', {'name': m_out})
                output_strings.append(ET.tostring(output_node))


            doc = minidom.parseString(ET.tostring(node))

            opfilename = long_node_title + '.node'
            with open(os.path.join(working_dir, opfilename), 'w') as f:
                f.write(doc.toprettyxml(indent="  "))
        