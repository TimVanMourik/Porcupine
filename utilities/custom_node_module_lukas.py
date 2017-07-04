""" An example of a module with custom nodes.

This module contains some custom Nipype nodes
(constructed with the Function interface), which
is converted to a Porcupine-compatible JSON file,
which can be subsequently imported in Porcupine.
"""

from nipype.pipeline import Node
from nipype.interfaces.utility import Function


def my_custom_function(in_arg1, in_arg2_default='!'):
    """ This is a dummy function, just for
    testing the Porcupine converter.

    Parameters
    ----------
    in_arg1 : str
        String to be concatenated with "Hello ..."
    in_arg2_default : str
        String to be concatenated with "Hello {in_arg1}";
        default = '!'
    
    Returns
    -------
    out : str
        Concatenated string
    """

    out = "Hello %s%s" % (in_arg1, in_arg2_default)
    return out

MyCustomFunction = Node(interface=Function(input_names=['in_arg1',
                                                        'in_arg2_default'],
                                           output_names=['out'],
                                           function=my_custom_function),
                        name='MyCustomFunc')


def get_scan_info(in_file):
    """ Get useful scan-parameters. 

    Function to extract some useful scan-parameters.

    Parameters
    ----------
    in_file : str
        Path to (functional!) nifti-image

    Returns
    -------
    TR : float
        Time-to-repetition of file
    """

    import nibabel as nib
    func = nib.load(in_file)
    header = func.header
    TR = header['pixdim'][4]
    return TR


GetScanInfo = Node(interface=Function(input_names=['in_file'],
                                      output_names=['TR'],
                                      function=get_scan_info),
                   name='GetScanInfo')