---
title: "The workflow-editor"
excerpt: "How to use the workflow-editor"
layout: single
author_profile : false
categories:
  - 1. Basics
permalink: /documentation/basics/workflow-editor
---

The workflow editor is the part of Porcupine you'll probably spend most of your
time building your pipeline. In this window, you'll initialize the nodes of
your pipeline and draw connections between them.

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/documentation/images/workflow_editor.png"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/documentation/images/workflow_editor.png"></a>
	<figcaption>The "workflow-editor" in Porcupine.</figcaption>
</figure>

### Nodes in Porcupine
When you open Porcupine, you'll start with an empty workflow-editor. To begin
building your pipeline, you'll have to initialize some nodes. A "node" represents
a specific operation within your pipeline, ranging from neuroscience-specific
operations like skullstripping or motion-correction to more generic operations
like file I/O.

Currently, Porcupine provides nodes based on interfaces from two frameworks:
*Nipype*, a Python-based software package providing wrappers for all major
neuroimaging software packages, and [*TvM*](https://github.com/TimVanMourik/OpenFmriAnalysis),
a MATLAB-based laminar analysis package developed by Porcupine's lead developer.

In this documentation, we'll focus on explaining how to build Nipype-based
pipelines in Porcupine.

### Initializing nodes
To start building pipelines, you'll of course need
some nodes! To initialize nodes, click the "Nodes" option in the left-upper
corner of Porcupine's GUI. This should yield three options: `Load Dictionary`
(more on this [later in the documentation](/Porcupine/documentation/advanced/custom-nodes)), `TvM`, and `Nipype`.

Moving your cursor on the `Nipype` option then shows you all the Nipype-interfaces
that Porcupine supports. Selecting, for example, `fsl` and, in turn, `preprocess`
shows you all the available nodes from FSL's preprocessing suite (including
`BET` and `FAST` from the image above).

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/documentation/images/init_nodes.png"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/documentation/images/init_nodes.png"></a>
	<figcaption>The "workflow-editor" in Porcupine.</figcaption>
</figure>

Clicking on one of these nodes (e.g. `fsl.BET`), then, creates a node in the workflow-editor!

## Connecting nodes
Now, suppose you've created an `fsl.BET` and an `fsl.FAST` node as in the above
example. Looking at, for example, the `fsl.BET` node, you see the name of the
interface (here "fsl.BET") at the top of the node. Note that you can simply change
this default name, for example if you want to give it a more intuitive name
(like "skullstrip" instead of "fsl.BET"), by clicking on it. Below the name of
the interface

##
