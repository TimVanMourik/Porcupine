---
title: "FEAT reconstruction"
excerpt: "A Porcupine-pipeline reconstructing FSL FEAT's analysis pipeline."
header:
  teaser: /examples/example_pipelines/FEAT_fsl_complete_firstlevel_and_secondlevel/porcupine_graph.png
layout: single
permalink: /examples/FEAT-example
---

{% assign example_path = 'examples/example_pipelines/FEAT_fsl_complete_firstlevel_and_secondlevel/' %}
{% assign caption = 'An example a full FSL-based first-level and second-level analysis' %}

This example pipeline expands the [previous firstlevel-analysis example](/Porcupine/examples/firstlevel-example)
with a complete preprocessing pipeline -- including temporal/spatial filtering
and a two-step registration process -- and a second-level analysis. The pipeline
is created such that is mimicks the pipeline implement in FSL preprocessing/analysis
tool "FEAT".

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_graph.png"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_graph.png"></a>
	<figcaption>{{ caption }}</figcaption>
</figure>

Check out the Porcupine-generated Python-script, Porcupine-pipeline, and
associated Dockerfile in our [Github repository](https://github.com/TimVanMourik/Porcupine/tree/example_workflows/docs/_{{ example_path }}) or download the files directly below.

[<i class="fa fa-download"></i> Download .pork-file][1]{: .btn}
[<i class="fa fa-download"></i> Download .py-file][2]{: .btn}
[<i class="fa fa-download"></i> Download Dockerfile][3]{: .btn}

[1]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_pipeline.pork
[2]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_generated_pipeline.py
[3]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/Dockerfile
