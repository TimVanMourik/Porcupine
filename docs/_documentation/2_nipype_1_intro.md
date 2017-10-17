---
title: "Nipype in Porcupine"
excerpt: "Introduction to generating Nipype code using Porcupine"
layout: single
author_profile : false
categories:
  - 2. Nipype-pipelines
permalink: /documentation/nipype/intro
---

Porcupine works well with interfaces specified by the Nipype package, which
provides wrappers for different neuroimaging software package (including
FSL, AFNI, ANTs, SPM, and Freesurfer) and additionally provides more generic
functionality for, e.g., file I/O and pipeline-specific utilities.

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/documentation/images/nipype_interfaces_edited.png"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/documentation/images/nipype_interfaces_edited.png"></a>
	<figcaption>Nipype modules that Porcupine interfaces with (click to enlarge)</figcaption>
</figure>

To effectively leverage Nipype in Porcupine, including Nipype's vision on
iterable input-ports (using "iterfields" and "iterables") and dynamically
generated ports, we need to delve a little deeper into these topics,
which will be the subject of this part of the documentation.
