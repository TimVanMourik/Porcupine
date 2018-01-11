---
title: "First-level analysis example"
excerpt: "An example of a first-level analysis (FSL-based) pipeline in Porcupine."
header:
  teaser: /examples/example_pipelines/firstlevel_fsl_and_custom_modules_example/porcupine_graph.png
layout: single
permalink: examples/firstlevel-example
---

{% assign example_path = 'examples/example_pipelines/firstlevel_fsl_and_custom_modules_example/' %}
{% assign caption = 'An example of a (FSL-based) first-level analysis' %}

This example pipeline loads both a functional MRI file and file with event
onsets and durations (in [BIDS-format](http://bids.neuroimaging.io/)) and
subsequently specifies a design and contrasts, and fits the design onto the
functional MRI file using a voxel-wise GLM (i.e. a mass-univariate first-level
analysis).

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_graph.png"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_graph.png"></a>
	<figcaption>{{ caption }}</figcaption>
</figure>

More specifically, this pipeline leverages the FSL modelling interfaces (`fsl.Level1Design`,
`fsl.FEATModel`, and `fsl.FILMGLS`). Also, because Nipype does not provide
an interface to load in BIDS-style event-files, we included a custom interface
that converts the information in the event file to a format that the rest of
the pipeline can work with. See the
[section on custom interfaces](/Porcupine/documentation/    advanced/custom-nodes)
in the documentation for more information on how to add your own interfaces/modules.

Check out the Porcupine-generated Python-script, Porcupine-pipeline, and
associated Dockerfile in our [Github repository](https://github.com/TimVanMourik/Porcupine/tree/example_workflows/docs/_{{ example_path }}) or download the files directly below.

[<i class="fa fa-download"></i> Download .pork-file][1]{: .btn}
[<i class="fa fa-download"></i> Download .py-file][2]{: .btn}
[<i class="fa fa-download"></i> Download Dockerfile][3]{: .btn}

[1]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_pipeline.pork
[2]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_generated_pipeline.py
[3]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/Dockerfile
