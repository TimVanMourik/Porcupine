---
layout: splash
author_profile: false
title: Getting started
permalink: /getting-started/

header:
  overlay_color: "#000"
  overlay_filter: "0.1"
  overlay_image: /assets/images/pipeline_lq.jpg
---

# What is Porcupine?
Porcupine is a software package that offers a graphical user interface (GUI) to
build reproducible analysis pipelines for (f)MRI data. In Porcupine, you can
create analysis pipelines by connecting "nodes" (analysis operations) to
each other. For example, one could create a preprocessing pipeline for structural
MRI, in which a "skullstripping node" (e.g. FSL's `BET` or AFNI's `3dSkullstrip`)
is connected to a "segmentation node" (e.g. FSL's `FAST` or SPM's `NewSegment`).

{% include figure image_path="/assets/images/example_anat_wf.png"
 alt="this is a placeholder image" caption="Example of a Porcupine workflow connecting FSL's BET and FAST." %}

## Why Porcupine?
While there are existing pipeline packages (such as LONI and Nipype), these packages
often require extensive technical knowledge and skills, which makes it difficult
for researchers unfamiliar with these computational practices to start building
analysis pipelines. However, describing one's analysis pipeline in code is
essential in improving transparency and reproducibility in (neuro)science.

Porcupine provides the best of both worlds: while it allows researchers to build
pipelines using Porcupine's GUI, it also generates the code that is needed to
run the pipeline created in the GUI. Currently, Porcupine supports two
pipeline-frameworks: [Nipype](https://nipype.readthedocs.io/en/latest/),
a Python-based pipelining package, and my own [Laminar Analysis Toolbox](https://github.com/TimVanMourik/OpenFmriAnalysis).

In the image below, you can see the Porcupine-workflow (left) and the Porcupine-generated
Nipype code (right) side-by-side.

{% include figure image_path="/assets/images/pork_py.png"
 alt="this is a placeholder image" caption="Porcupine generates the code necessary to run your pipeline." %}

## Porcupine improves reproducibility
For Nipype-based pipelines, Porcupine doesn't only create the *code* corresponding
to your pipeline, but also a *Dockerfile* that complements your pipeline. Building
this Dockerfile creates a Docker-image that - together with your Porcupine-generated code -
makes your pipeline completely reproducible from beginning to end.

{% include figure image_path="/assets/images/docker_code.png"
 alt="this is a placeholder image" caption="Porcupine also generates a Dockerfile complementary to your pipeline." %}

# Get started!
To get started with building pipelines in Porcupine, [download](../download) and install
Porcupine first. We provide installers for Windows and Mac OS. Then,
check out our [example gallery](../examples) for inspiration or check out our
[documentation](../documentation) for more information on how to work with Porcupine. If you're interested in more background information of Porcupine, take a look at [this presentation](../assets/images/Porcupresentation.pdf)!

**Beware!** On Mac, there is a chance that you can get a pop-up that Porcupine does not want to open straight away, depending on your security settings. Your Mac might not like apps that do not come straight out of the app store. You can eaily open Porcupine by going to 'System Preference' -> 'Security & Privacy' and click on 'Open Anyway'
{: .notice--warning}
