---
title: "Iterables and MapNodes in Nipype-based pipelines"
excerpt: "How to implement iterables and MapNodes in Nipype-pipelines in Porcupine"
layout: single
author_profile : false
categories:
  - 2. Nipype-pipelines
permalink: /documentation/nipype/iterables-and-mapnodes
---

Using the Nipype-interfaces in combination with Porcupine's ability to manually
add input and output-ports allows you to build basically any Nipype-based
pipeline you can imagine. Howevever, we haven't discussed how Porcupine implements
[iterables and iterfields/MapNodes](), i.e. Nipype's approach to iterate nodes and entire
pipelines over a range of parameters.

### Iterables vs. iterfields/MapNodes
The difference between iterables and the iterfields/MapNode construct within Nipype
is subtle but important. Basically, an iterable defines a set of values for a given
input-port of a node across which the *entire pipeline* will iterate (from that node onwards).

For example, suppose you define a spatial smoothing pipeline for a single functional MRI file.
You could define the smoothing kernel port of your smoothing node (e.g. the `fwhm`
input-port from the `fsl.SUSAN` smoothing node) as an iterable, instructing it
for example to iterate over the values 3, 5, and 7 (corresponding thus to a
FWHM smoothing kernel of 3, 5, and 7 mm respectively). This will basically repeat
the entire pipeline (from the smoothing node onwards) for these different values of
your smoothing kernel.

The iterfield/MapNode construct, on the other hand, does not repeat the entire
pipeline for a given set of values, but repeats only the operation of the node itself
for a given set of values. The "iterfield" corresponds to the input-port that you
want to iterate over, while `MapNode` refers to the Nipype-specific type of node  
that allows repetition (or "expansion") of the node itself for the different values
in the iterfield. After expansion of the node into different nodes corresponding
to the different values of the iterfield (e.g. a smoothing node with FWHM=3, a smoothing
node with FWHM=5, and a smoothing node with FWHM=7), the outputs of these nodes
(the three files smoothed with the different FWHM parameters) are simply concatenated
into a list, which is (when connected) simply passed onto the next node, whether
that's a MapNode or a simple node.

See the [Nipype docs](http://nipype.readthedocs.io/en/latest/users/mapnode_and_iterables.html)
for more information on (the difference between) iterfields/MapNodes and iterables

### Iterables/iterfields/MapNodes in Porcupine
In Porcupine, you can set an input-port to an iterable or iterfield using the
blue circular arrow-icon next to the input-port in the node editor. Importantly,
whether the input-port will turn into an iterable or an iterfield *depends on
whether the input-port's value is hard-coded or depends on a connection with
another node*. If it's hard-coded, it'll turn into an iterable; it it receives
a connection from another node, it'll turn into an iterfield.

For example, in the image below, the `T1_file` field from the `IdentityInterface`
node is an iterable (the values, `['sub-01_T1w.nii.gz', 'sub-02_T1w.nii.gz']`,
are hard-coded) while the `in_file` input-port from the FSL BET node is an
iterfield (which thus, Nipype-technically, turns the BET-node into a MapNode),
because this input-port receives a connection from another node (the
`IdentityInterface` node):

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/documentation/images/mapnode_vs_iterable.png"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/documentation/images/mapnode_vs_iterable.png"></a>
	<figcaption>Difference between iterables and iterfields in Porcupine (click to enlarge)</figcaption>
</figure>

For more examples on iterables/iterfields/mapnodes (that you can download and run yourself!),
check out the [iterable example](/Porcupine/examples/iterables-example) and
the [MapNode example](/Porcupine/examples/mapnode-example) in our gallery!
