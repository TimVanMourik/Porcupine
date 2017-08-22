""" An example of a module with custom nodes.

This module contains some custom Nipype nodes
(constructed with the Function interface), which
is converted to a Porcupine-compatible JSON file,
which can be subsequently imported in Porcupine.
"""

from nipype.pipeline import Node
from nipype.interfaces.utility import Function


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


GetScanInfo = Function(input_names=['in_file'],
                       output_names=['TR'],
                       function=get_scan_info)
