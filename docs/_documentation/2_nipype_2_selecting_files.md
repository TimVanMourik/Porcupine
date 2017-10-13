---
title: "Selecting files"
excerpt: "Using the SelectingFiles or DataGrabber functions"
layout: single
author_profile : false
categories:
  - 2. Nipype-pipelines
permalink: /documentation/nipype/select-files
---

The first thing you likely want to do in buildign a pipeline is selecting the files that you want to work with. Nipype has several functions that you could use for this, like the `SelectFiles`, the `DataGrabber`, or the `S3DataGrabber`. The first one gets data from disk directly, the second gets data from disk based on a _template_, the third one collects data from an online (Amazon) repository, a so-called s3-bucket.

Unfortunately, these file referencing functions are immediately the most counter-intuitive ones in Porcupine. When you create one of these modules, you won't get any output ports, whereas that's exactly what you want to use them for! The reason is that you will have to add these yourself and give them a name: Nipype isn't very good with coming up with names itself. We here show how to do this.

### The `SelectFiles` interface
Now, as Porcupine does not allow to set initialization parameters (only prespecified
input-ports), we made sure that you can solve this issue by manually adding ports.
Specifically, you can mimick the `templates` dictionary by adding a new input/output port
for each key; in turn, Porcupine will make sure to generate Nipype-code that conforms
to the proper initialization. See the gif below for a demonstration:

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/documentation/images/select_files.gif"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/documentation/images/select_files.gif"></a>
	<figcaption>How to use SelectFiles using manual ports (click to enlarge)</figcaption>
</figure>

### The `DataGrabber` interface

### The `S3DataGrabber` interface
