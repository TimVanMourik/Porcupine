---
title: "Simple example"
excerpt: "An example showing Porcupine's basic features"
header:
  teaser: /examples/example_pipelines/simple_example/porcupine_graph.png
layout: single
permalink: /examples/simple-example
---

{% assign example_path = 'examples/example_pipelines/simple_example/' %}
{% assign caption = "A simple example pipeline performing skullstripping in Porcupine" %}

This example pipeline showcases the some basic functionality of a (Nipype-based)
Porcupine pipeline, which defines a T1-weighted structural scan as input,
performs skullstripping on it, and writes the result to disk.

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_graph.png"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_graph.png"></a>
	<figcaption>{{ caption }}</figcaption>
</figure>

This pipeline, like all the example pipelines we provide, defines the input-data
as data from an [openneuro](https://openneuro.org/public/datasets) Amazon
repository (called an "S3 bucket"). In the first node, we define the input as
a single T1-weighted structural scan from the
[ds-000101](https://openneuro.org/datasets/ds000101/versions/00004) dataset from
the openneuro repository. Then, we connect this to a skullstripping node
(performed by FSL BET), and finally write the skullstripped data to disk in the
last node.

The nodes in the pipeline are all based on Nipype-interfaces. Nipype provides
a comprehensive set of interfaces for different neuroimaging software packages,
in addition to more generic functionality relating to file I/O and pipeline-specific
operations. In this example pipeline, we specifically use Nipype's `S3DataGrabber`
interface in our first node to download a single T1-weighted file from an
openneuro repository, which we subsequently connect to the Nipype-based FSL
BET node. The result of the skullstrip operation by the BET-node is then written
to disk using the `DataSink` node from Nipype.

Check out the Porcupine-generated Python-script, Porcupine-pipeline, and
associated Dockerfile in our [Github repository](https://github.com/TimVanMourik/Porcupine/tree/example_workflows/docs/_{{ example_path }}) or download the files directly below.

[<i class="fa fa-download"></i> Download .pork-file][1]{: .btn}
[<i class="fa fa-download"></i> Download .py-file][2]{: .btn}
[<i class="fa fa-download"></i> Download Dockerfile][3]{: .btn}

[1]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_pipeline.pork
[2]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_generated_pipeline.py
[3]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/Dockerfile
