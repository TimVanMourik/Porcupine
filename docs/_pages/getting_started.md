---
layout: splash
author_profile: false

header:
  overlay_color: "#000"
  overlay_filter: "0.1"
  overlay_image: /_pages/assets/images/pipeline_lq.jpg

feature_row:
  - image_path: /_pages/assets/images/pipeline_example.jpg
    alt: "example"
    title: "Human Connectome"
    excerpt: "An example of a pipeline."
    #url: "/_pages/assets/example_pipeline/"
    #btn_label: "Human Connectome"
  - image_path: /_pages/assets/images/pipeline_example.jpg
    alt: "example"
    title: "NeuroImage"
    excerpt: "An example of a pipeline."
    #url: "/_pages/assets/example_pipeline/"
    #btn_label: "Human Connectome"
  - image_path: /_pages/assets/images/pipeline_example.jpg
    alt: "example"
    title: "Other famous Study"
    excerpt: "An example of a pipeline."
    #url: "/_pages/assets/example_pipeline/"
    #btn_label: "Human Connectome"
---


# Porcupine
This program is meant for creating analysis pipelines for fMRI analysis (and perhaps for in the future). At the moment, this works only for NiPype pipelines, but interfaces to other packages are also in development.

## Installation
Just download the installer files. Currently, there is only an installer for Windows. Mac and Linux installer files will follow soon.

## Compilation
If you want to contribute and hack around yourself, you should first compile it. This is easily done on any platform with <a href="https://www.qt.io/download/">Qt Creator</a>.

Currently, it's been tested on Mac, Windows and Linux with the latest version of Qt (5.7.0) and Qt Creator (4.1.0). If that's installed, basically pressing the big green button is the only thing you need to make it compile and run.

## Modules
Porcupine features interfaces to
* My own [fMRI analysis toolbox](https://github.com/TimVanMourik/OpenFmriAnalysis), including layer specific fMRI
* [NiPype](https://github.com/nipy/nipype)

## Porcupine in action: examples that have not yet been created
{% include feature_row %}
