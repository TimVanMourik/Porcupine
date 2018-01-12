---
title: "Iterable example"
excerpt: "An example using an iterable in Porcupine."
header:
  teaser: /examples/example_pipelines/iterable_example/porcupine_graph.png
layout: single
permalink: /examples/iterables-example
---

{% assign example_path = 'examples/example_pipelines/iterable_example/' %}
{% assign caption = 'An example of a skullstripping pipeline iterated over different subjects.' %}

This example pipeline adjusts the previous example of a simple skullstripping
pipeline such that it allows iteration ("looping") over different subjects.

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_graph.png"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_graph.png"></a>
	<figcaption>{{ caption }}</figcaption>
</figure>

Using Nipype-interfaces again, we added an `IdentityInterface` node that contains
an input-port `sub_id` that contains a list `["sub-01", "sub-02"]`. This input-port
is set as an "iterable" (see [our docs](/Porcupine/documentation/nipype/iterables-and-mapnodes)
for more info on iterables in Porcupine), such that it "feeds" each value in the
`sub_id` input-port one-by-one into the skullstripping pipeline, effectively
creating a skullstripping pipeline looped across the T1-weighted structural scans
of two subjects.

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/iterable_port.png"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/iterable_port.png"></a>
	<figcaption>"The sub-id input-port is here set as an iterable, allowing looping over the two sub-id values." </figcaption>
</figure>

Note that the value of `sub_id` (which "updates" after every iteration) is also
connected to the `container` input-port from the `DataSink` node, which makes
sure that each skullstripping result is written to a subject-specific sub-directory.

Check out the Porcupine-generated Python-script, Porcupine-pipeline, and
associated Dockerfile in our [Github repository](https://github.com/TimVanMourik/Porcupine/tree/example_workflows/docs/_{{ example_path }}) or download the files directly below.

[<i class="fa fa-download"></i> Download .pork-file][1]{: .btn}
[<i class="fa fa-download"></i> Download .py-file][2]{: .btn}
[<i class="fa fa-download"></i> Download Dockerfile][3]{: .btn}

[1]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_pipeline.pork
[2]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_generated_pipeline.py
[3]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/Dockerfile
