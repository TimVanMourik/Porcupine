---
title: "Selecting files"
excerpt: "Using the SelectingFiles or DataGrabber functions"
layout: single
author_profile : false
categories:
  - 2. Nipype-pipelines
permalink: /documentation/nipype/select-files
---

The first thing you likely want to do in building a pipeline is selecting the files
that you want to work with. Nipype has several interfaces that you could use for this,
like the `SelectFiles`, the `DataGrabber`, or the `S3DataGrabber`. The first one
gets data from disk directly, the second gets data from disk based on a _template_,
the third one collects data from an online (Amazon) repository, a so-called s3-bucket.

We highly recommend to use the `SelectFiles` interface to select files for
your pipeline, because it is much easier (and intuitive) to use than the
`DataGrabber` interface. In the rest of this section, we'll showcase how to
use `SelectFiles` nodes in your Porcupine pipeline to select files from disk.

## Scenario sketch
Before we explain how to use `SelectFiles`, let's sketch out a scenario.
Suppose a researcher has a ([BIDS-formatted](bids.neuroimaging.io)) dataset,
consisting of structural MRI-scans (a single T1-weighted scan) and functional
MRI-scans (two runs of fMRI acquisition during a nback-task) of 10 subjects.
This data may be stored in the researcher's home-directory of his/her laptop,
in the folder `~/data`, which is organized as follows:

[ folder tree ]

Using Porcupine, this researcher wants to implement a simple pipeline that
calculates a registration for each functional file from functional space to
T1-space. Accordingly, the workflow needs to do the following (for each subject):

1. Skullstrip the T1-scan
2. Extract the first volume of each functional scan
3. Register each volume to the skullstripped T1-scan

We'll use this hypothetical pipeline to walk you through file I/O in
Porcupine using `SelectFiles` in the rest of this section.

## Using the `SelectFiles` interface in Porcupine
In this section, we'll walk you through increasingly complex uses of the
`SelectFiles` interface to select files for Porcupine pipelines.

### A simple example: selecting a single file
Now, let's start simple: suppose we want to select just one file - the T1-scan
from subject 1 (sub-01) for the skullstripping part of our pipeline (we'll extend
the pipeline in the following examples). We'll
create a `SelectFiles` node in Porcupine, but you'll notice that it doesn't list
any output-ports in the workflow and node editor! This is because `SelectFiles`
expects you to create the output-ports yourself (this refers to Nipype's
"dynamic ports" construct; you can read more on this in the
[corresponding section]() of the documentation).

Suppose you want to name the output-port of `SelectFiles` "anat". In that case, you need to
add a custom port with the name "anat", which you can do as follows: click the
"Add port" button at the bottom of the node in the node editor, enter the name
("anat"), and select "Both" (see also gif below). You should now see a "hybrid"
input/output-port in the workflow editor and a new field named "anat" in the
node-editor!

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/documentation/images/select_files.gif"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/documentation/images/select_files.gif"></a>
	<figcaption>How to use SelectFiles using manual ports (click to enlarge)</figcaption>
</figure>

Now you need to tell the `SelectFiles` node where it can find the T1-file on disk.
To do so, we simply fill in the path in the "anat" field in the node editor:

[ img ]

Then, create an FSL `BET` node for the skullstripping operation and connect
the `anat` output-port of `SelectFiles` with the `in_file` input-port from
the `BET` node, and done! We have a fully functioning skullstripping "pipeline"!

### Selecting multiple files
For our pipeline, however, 

## Writing outputs to disk using `DataSink`
