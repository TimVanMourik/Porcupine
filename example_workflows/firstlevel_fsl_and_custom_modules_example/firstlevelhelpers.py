from nipype.interfaces.utility import Function
from nipype.pipeline import Node


def tsv2subjectinfo(in_file, exclude=None):

    import pandas as pd
    from nipype.interfaces.base import Bunch
    import numpy as np

    events = pd.read_csv(in_file, sep=str('\t'))

    if exclude is not None:  # not tested
        events.drop(exclude, axis=1, inplace=True)


    conditions = sorted(events['trial_type'].unique())
    onsets = [events['onset'][events['trial_type'] == tt].tolist() for tt in conditions]
    durations = [events['duration'][events['trial_type'] == tt].tolist() for tt in conditions]
    
    if 'weight' in events.columns:
    	amplitudes = [events['weight'][events['trial_type'] == tt].tolist() for tt in conditions]
    else:
    	amplitudes = [np.ones(len(d)) for d in durations]

    bunch = Bunch(conditions=conditions,
                  onsets=onsets,
                  durations=durations,
                  amplitudes=amplitudes)
    
    return bunch


Tsv2subjectinfo = Function(function=tsv2subjectinfo, input_names=['in_file', 'exclude'],
        	               output_names=['subject_info'])

