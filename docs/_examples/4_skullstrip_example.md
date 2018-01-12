---

title: "Skullstrip example"
excerpt: "An example of a skullstripping pipeline in Porcupine."
header:
  teaser: /examples/example_pipelines/skullstrip_afni_ants_example/porcupine_graph.png
layout: single
permalink: /examples/skullstrip-example
---

{% assign example_path = 'examples/example_pipelines/skullstrip_afni_ants_example' %}
{% assign caption = 'Skullstripping workflow including bias field correction and intensity harmonization' %}

This example pipeline reconstructs the skullstripping-pipeline originally
defined in the [niworkflows Python package](https://github.com/poldracklab/niworkflows)
from the [Poldrack-lab](https://poldracklab.stanford.edu/). This pipeline
loads a T1-weighted structural scan, applies bias field correction (using ANTs)
and intensity harmonization (using AFNI), skullstrips the image, and finally
writes the results to disk.

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_graph.png"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_graph.png"></a>
	<figcaption>{{ caption }}</figcaption>
</figure>

Note that this pipeline includes Nipype-based nodes from three different
major neuroimaging packages (ANTs, AFNI, and FSL).

Check out the Porcupine-generated Python-script, Porcupine-pipeline, and
associated Dockerfile in our [Github repository](https://github.com/TimVanMourik/Porcupine/tree/example_workflows/docs/_{{ example_path }}) or download the files directly below.

[<i class="fa fa-download"></i> Download .pork-file][1]{: .btn}
[<i class="fa fa-download"></i> Download .py-file][2]{: .btn}
[<i class="fa fa-download"></i> Download Dockerfile][3]{: .btn}

[1]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_pipeline.pork
[2]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_generated_pipeline.py
[3]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/Dockerfile
