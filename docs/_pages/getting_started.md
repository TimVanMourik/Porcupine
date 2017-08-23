---
layout: splash
author_profile: false
title: Getting started

header:
  overlay_color: "#000"
  overlay_filter: "0.1"
  overlay_image: /_pages/assets/images/pipeline_lq.jpg

feature_row:
  - image_path: /_pages/assets/images/afni_skullstrip_workflow.png
    alt: "example"
    title: "Skullstrip workflow"
    excerpt: "Example of ANFI/ANTs-based skullstrip workflow"
    #url: "/_pages/assets/example_pipeline/"
    #btn_label: "Human Connectome"
  - image_path: /_pages/assets/images/fsl_restingstate_preproc_workflow.png
    alt: "example"
    title: "Resting-state preprocessing workflow"
    excerpt: "Example of an FSL-based rs-fMRI preprocessing workflow"
    #url: "/_pages/assets/example_pipeline/"
    #btn_label: "Human Connectome"
  - image_path: /_pages/assets/images/pipeline_example.jpg
    alt: "example"
    title: "Other famous Study"
    excerpt: "An example of a pipeline."
    #url: "/_pages/assets/example_pipeline/"
    #btn_label: "Human Connectome"

#climo:
#  - image_path: /_pages/assets/images/climo_porcupine.jpg
#    url: https://lizclimo.tumblr.com" target="_blank
#    alt: Liz Climo
---

# Porcupine
This program is meant for creating analysis pipelines for fMRI analysis. By dragging and dropping modules into an editor, you can simply create a workflow. The code for your analysis is automatically generated. Just download the installer files and get started. Currently, there is a Windows and a Mac installer. Also, it can be run within a docker image.

## Modules
Porcupine features modules to create a pipeline for:
* [NiPype](https://github.com/nipy/nipype), which itself connects to all major MRI analysis software packages
* [neurodocker](https://github.com/kaczmarj/neurodocker), a tool to automatically create Docker files
* My own [fMRI analysis toolbox](https://github.com/TimVanMourik/OpenFmriAnalysis), including layer specific fMRI

## Porcupine in action: some example workflows
{% include feature_row %}

## Documentation
Documentation will follow, but most of the program is quite straightforward. Just drag in your modules, wire them up, and your analyis code is automatically generated.

{% include feature_row id="climo"  type="center" %}
