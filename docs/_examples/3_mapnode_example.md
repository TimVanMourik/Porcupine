---
title: "Mapnode example"
excerpt: "An example using a MapNode in Porcupine."
header:
  teaser: /examples/example_pipelines/multirun_mapnode_example/porcupine_graph.png
layout: single
permalink: /examples/mapnode-example
---

{% assign example_path = 'examples/example_pipelines/multirun_mapnode_example/' %}
{% assign caption = 'Skullstripping pipeline utilizing a MapNode/iterfield' %}

In this example, we defined a simple motion-correction workflow, in which we
load two functional MRI files (belong to two different runs) from two subjects
each, perform motion-correction on them, and write the results to disk again.
In addition to iteration over subjects using the two subjects as an iterable,
we utilize MapNodes (a Nipype-specific pipeline object; see
[the corresponding section on MapNodes in our docs](/Porcupine/documentation/nipype/iterables-and-mapnodes))
to also "loop" our pipeline across the two different runs.

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_graph.png"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_graph.png"></a>
	<figcaption>{{ caption }}</figcaption>
</figure>

Like the previous skullstripping pipeline, this motion-correction defines
`sub_id` as an iterable in the `IdentityInterface` to loop over subjects,
but additionally makes the motion-correction node (which interfaces with
AFNI `3dvolreg`) a `MapNode` by setting the `in_file` input-port to be an
iterfield, allowing to further "loop over" multiple inputs (here: two functional runs).

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/mapnode.png"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/mapnode.png"></a>
	<figcaption>The in_file port is set to operate over a list of inputs."</figcaption>
</figure>

Note that the way you set an input-port to be *iterable* is exactly the same as
the way you set *iterfield* in Porcupine, that is, by unchecking the circular
arrow next to the input-port in the node editor. Whether the input-port becomes
an iterable or an iterfield (converting the node into a MapNode object) depends
entirely on whether the value of this specific input port is defined in the
node itself (such as in the `sub_id` port in the `IdentityInterface` node) or
whether the input-port receives input from another node (such as the `in_file`
input-port in the AFNI `Volreg` node, which receives a list of functional MRI
files from the `S3DataGrabber` node).

For a more elaborate explanation on how
Porcupine handles iterables and MapNodes/iterfields, see the [corresponding section
in the documentation]().

Check out the Porcupine-generated Python-script, Porcupine-pipeline, and
associated Dockerfile in our [Github repository](https://github.com/TimVanMourik/Porcupine/tree/example_workflows/docs/_{{ example_path }}) or download the files directly below.

[<i class="fa fa-download"></i> Download .pork-file][1]{: .btn}
[<i class="fa fa-download"></i> Download .py-file][2]{: .btn}
[<i class="fa fa-download"></i> Download Dockerfile][3]{: .btn}

[1]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_pipeline.pork
[2]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_generated_pipeline.py
[3]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/Dockerfile
