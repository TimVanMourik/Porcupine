---
title: "Manually adding ports"
excerpt: "How to mimick Nipype's dynamic ports using manually added ports"
layout: single
author_profile : false
categories:
  - 2. Nipype-pipelines
permalink: /documentation/nipype/dynamic-ports
---

In the previous chapter we already added some manual ports, and here we dive a little deeper in the underlying reasons. Most of Nipype nodes have prespecified input and output-ports. Nipype calls these ports "InputSpecs" and "OutputSpecs", which are Python objects whose attributes correspond to the interface's inputs and outputs. After initialization of an FSL BET interface for example, these inputs and outputs (as defined in the InputSpec and OutputSpec) are available from the interface's `input` and (after running the interface) the `output` attributes:

```python
>>> from nipype.interfaces.fsl import BET
>>> from nipype.pipeline import Node
>>> bet_node = Node(BET(), name='BET')
>>> bet_node.inputs

args = <undefined>
center = <undefined>
environ = {'FSLOUTPUTTYPE': 'NIFTI_GZ'}
frac = <undefined>
...

>>> bet.outputs

inskull_mask_file = <undefined>
inskull_mesh_file = <undefined>
mask_file = <undefined>
meshfile = <undefined>
out_file = <undefined>
...
```

### Dynamic ports
Some Nipype-interfaces, however, do not have a prespecified set of inputs and
outputs. These InputSpecs and OutputSpecs are *dynamic*, in the sense that
they are dynamically created based on parameters during initialization of the
interface. A clear example of such an interface that uses this dynamic input/output
generation is Nipype's `IdentityInterface`, an interface that performs
a simple "identity transformation" (i.e., just transfer input to output without
doing anything to it). This interface needs the parameter `fields`
(a list of strings) upon initialization. During initialization of this interface,
each value from the fields parameter will be used to dynamically create  *both*
an input *and* an output with the same name.

So, suppose I initialize a node based on the `IdentityInterface` with the
`fields` parameters set to `['A', 'B']`, then it will create two inputs and
outputs with the names `A` and `B`:

```python
>>> from nipype.interfaces.utility import IdentityInterface
>>> from nipype.pipeline import Node
>>> ii_node = Node(IdentityInterface(fields=['A', 'B']), name='BET')
>>> ii_node.inputs

A = <undefined>
B = <undefined>

>> ii_node.outputs

A = <undefined>
B = <undefined>
```

### Handling dynamic ports in Porcupine
Porcupine is able to set the values of *existing* input-ports, but cannot do
so for ports that are dynamically generated. To circumvent this exception, we
added the option to manually add input and/or output-ports yourself! As should
become clear from the figure below, it's as easy as selecting "Add port" button
(located at the very bottom of each node in the node editor), choosing the port's
name, and indicating whether it will be an input, output, or both input/output
port (as in the `IndentityInterface`):

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/documentation/images/manual_ports.gif"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/documentation/images/manual_ports.gif"></a>
	<figcaption>Adding custom ports in Porcupine (click to enlarge)</figcaption>
</figure>

As you can see, after adding the input/output port `my_custom_port` in the above gif,
both the node in the workflow editor is updated and the `IdentityInterface` is
initialized correctly with the `fields` parameter, rendering valid Nipype-code.

### Another example: the `Merge` interface
The previous two examples (the `IdentityInterface` and `SelectFiles` interface)
were examples in which a particular initialization parameter (e.g. `fields`) is
*necessary*; that is, the Nipype-script would crash if the interface would be
initialized without said parameter.

There are other interfaces, however, that depend on dynamically created ports,
but *not* (necessarily) on a mandatory initialization parameter. For these interfaces,
we didn't need to write an exception for our Porcupine code-generator (as we did for
the `IdentityInterface` and `SelectFiles` interfaces), because the user can simply
add the necessary ports him/herself.

This sounds perhaps a little abstract, so let's look at an example of such an
interface that needs manually added ports but not (necessarily) a mandatory
initialization parameter: the `Merge` interface.

The `Merge` interface merges the values from a variable amount of input-ports
(which should be named `in1`, `in2`, ..., `inx` for an `x` number of input-ports)
into a list. Suppose I want to merge two inputs using the `Merge` interface;
in that case, I would need to create two custom input-ports named `in1` and `in2`,
as shown below:

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/documentation/images/merge.gif"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/documentation/images/merge.gif"></a>
	<figcaption>How to use Merge using manual ports (click to enlarge)</figcaption>
</figure>

### Another example: the `DataSink` interface
As a last example of using manually added ports, let's look at the Nipype's
`DataSink` interface. This is already covered a little bit in the [previous chapter](/documentation/nipype/select-files). This interface is somewhat special because it creates
input-ports based on how connections to the `DataSink` node are defined.
In other words, if I connect for example the `out_file` of an FSL BET-node to
the `DataSink` interface using the default Nipype syntax ...

```python
workflow.connect(BET_node, 'out_file', datasink_node, 'skullstrip_results')
```

... then the input-port `skullstrip_results` is actually dynamically generated.
In Porcupine, you can solve this by simply manually adding a `skullstrip_results`
input-port to your `DataSink` node, as shown below:

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/documentation/images/datasink.gif"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/documentation/images/datasink.gif"></a>
	<figcaption>How to use DataSink using manual ports (click to enlarge)</figcaption>
</figure>

 Note that you should name the input-ports of the `DataSink` node in Porcupine
 just like you would in Nipype, i.e., using periods (`.`) and @ for sinking
 results to the same output-directory (or subdirectory when you use @).
