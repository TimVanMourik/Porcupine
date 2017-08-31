---
title: "Iterable example"
excerpt: "An example using an iterable in Porcupine."
header:
  teaser: assets/images/examples/iterable_example_porcupine_graph.png
layout: single
permalink: /iterables-example
---

This example pipeline adjusts the previous example of a simple skullstripping
pipeline such that it allows iteration over different subjects. In other words,
it loops the previously defined skullstripping pipeline across different subjects.

{% include figure image_path="/examples/example_pipelines/iterable_example/porcupine_graph.png"
   caption="An example of a skullstripping pipeline iterated over different subjects." %}

Using Nipype-interfaces again, we added an `IdentityInterface` node that contains
an input-port `sub_id` that contains a list `["sub-01", "sub-02"]`. This input-port
is set as an "iterable" (see [link]() for more info on iterables in Porcupine),
such that it "feeds" each value in the `sub_id` input-port one-by-one into the
skullstripping pipeline, effectively creating a skullstripping pipeline looped
across the T1-weighted structural scans of two subjects. Note that the value of
`sub_id` (which "updates" after every iteration) is also connected to the
`container` input-port from the `DataSink` node, which makes sure that each
skullstripping result is written to a subject-specific sub-directory.

Check out the Porcupine-generated Python-script, Porcupine-pipeline, and
associated Dockerfile in our [Github repository](https://github.com/TimVanMourik/Porcupine/tree/example_workflows/docs/_examples/example_pipelines/iterable_example)
or download the files directly below.

[<i class="fa fa-download"></i> Download .pork-file][1]{: .btn}
[<i class="fa fa-download"></i> Download .py-file][2]{: .btn}
[<i class="fa fa-download"></i> Download Dockerfile][3]{: .btn}

[1]:{{ site.url }}{{ site.baseurl }}/examples/example_pipelines/iterable_example/porcupine_pipeline.pork
[2]:{{ site.url }}{{ site.baseurl }}/examples/example_pipelines/iterable_example/porcupine_generated_workflow.py
[3]:{{ site.url }}{{ site.baseurl }}/examples/example_pipelines/iterable_example/Dockerfile
