---
title: "rs-fMRI preproc example"
excerpt: "An example a resting state fMRI preprocessing pipeline in Porcupine."
header:
  teaser: /examples/example_pipelines/resting_preproc_fsl_example/porcupine_graph.png
layout: single
permalink: /examples/rs-fmri-preproc-example
---

{% assign example_path = 'examples/example_pipelines/resting_preproc_fsl_example' %}
{% assign caption = 'rs-fMRI preprocessing pipeline using FSL functionality' %}

This example showcases a preprocessing pipeline for resting state fMRI (rs-fMRI)
data, which loads a functional MRI file, applies slice time correction
slice-time corrected, motion-corrected, regresses out the first two principal
components within a noise ROI based on the 2% highest variance voxels (also known as
[tCompCor](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC2214855/)), applies
a high-pass filter, and writes the preprocessed file to disk.

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_graph.png"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_graph.png"></a>
	<figcaption>{{ caption }}</figcaption>
</figure>

This pipeline is a reconstruction of the rs-fMRI pipeline from the
[Nipype website](https://nipype.readthedocs.io/en/latest/interfaces/generated/workflows.rsfmri/fsl.resting.html).

Check out the Porcupine-generated Python-script, Porcupine-pipeline, and
associated Dockerfile in our [Github repository](https://github.com/TimVanMourik/Porcupine/tree/example_workflows/docs/_{{ example_path }}) or download the files directly below.

[<i class="fa fa-download"></i> Download .pork-file][1]{: .btn}
[<i class="fa fa-download"></i> Download .py-file][2]{: .btn}
[<i class="fa fa-download"></i> Download Dockerfile][3]{: .btn}

[1]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_pipeline.pork
[2]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_generated_pipeline.py
[3]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/Dockerfile
