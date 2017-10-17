---
title: "Using custom Nipype-nodes in Porcupine"
excerpt: "How to convert and load custom Nipype-nodes"
layout: single
author_profile : false
categories:
  - 3. Advanced usage
permalink: /documentation/advanced/custom-nodes
---

Nipype's built-in functionality offers enough flexibility to build complex
preprocessing and analysis pipelines, but users inevitably will run into
scenarios that require functionality that is not included in Nipype's collection
of interfaces.

In those scenarios, Nipype offers the possibility to wrap a custom written
Python function in their `Function` interface, effectively converting your
function into a Nipype-style interface with compatible inputs and outputs
(see [the Nipype docs](http://nipype.readthedocs.io/en/latest/users/function_interface.html)
for more info).

### Converting your custom nodes to a Porcupine-readable format
In Porcupine, we've added an option to load in these custom-mode `Function`-wrapped
interfaces. Porcupine cannot load in these interfaces directly, however. Instead,
any interface should be converted to a JSON-format compatible with Porcupine. Doing
this manually would be a lot of tedious work, so we've written a short Python program
that converts your Python module (which should contain `Function`-based interfaces)
into a Porcupine-compatible JSON-file (which can be downloaded at the bottom of the page).

The program -- `parse_custom_module.py` -- can be invoked as follows:
```
usage: parse_custom_module.py [-h] [-m MODULE] [-v] [-a]

Parse custom modules w/Nipype nodes.

optional arguments:
  -h, --help  show this help message and exit
  -m MODULE   Module to parse
  -v VERBOSE  Print much more output ...
  -a          Whether to add the absolute path of the module to the Nipype-
              script; if not set (default), the module is NOT added to the
              PYTHONPATH, and should thus be located in the directory from
              which the pipeline is run
```

The module you choose to convert using this program should be a Python module
(just a file ending in `.py`) including one or more `Function`-interfaces wrapping
your own custom functions. After adding your Python-to-JSON converted file to Porcupine,
each custom `Function`-interface will appear as a separate node/interface in
Porcupine's menu-bar.

### Adding your custom module to Porcupine
Once you converted your Python module with custom interfaces to the Porcupine-compatible
JSON-format, you can load in the JSON-file by clicking the `Nodes` > `Load Dictionary`
option in the menu-bar. Below, we showcase an example of how to do this, based
on the [firstlevel-analysis example]() from our example gallery, in which
we defined an interface (in the file `firstlevelhelpers.py`) to convert
event-info in [BIDS-formatted](http://bids.neuroimaging.io/) tsv-files to a
format that Nipype can deal with:

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/documentation/images/custom_module.gif"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/documentation/images/custom_module.gif"></a>
	<figcaption>Adding custom interfaces to Porcupine (click to enlarge)</figcaption>
</figure>

### Running pipelines with custom nodes
Importantly, once you've build your pipeline with custom nodes and you want to
run the Porcupine-generated Python-script, make sure your custom Python-modules
(that is, the `*.py` files with custom `Function`-interfaces) are located in the
directory you're running your script from. For example, suppose you named your
custom Python module "helperfunctions.py" (and thus its JSON-equivalent "helperfunctions.JSON")
and your Porcupine-generated script "porcupine_generated_pipeline.py". If you
want to run your the pipeline defined in "porcupine_generated_pipeline.py" by
running ...

```
$ python porcupine_generated_pipeline.py
```

... then make sure the "helperfunctions.py" file is located in the same directory.
(This is because Porcupine adds `import helperfunctions` to the script's imports,
which will only work if "helperfunctions.py" is located in the current working directory,
or when it's added to the PYTHONPATH; this latter option can be enabled by running
`parse_custom_module` with the `-a` flag.)

### Downloads
Download the `parse_custom_module.py` script and an example module with a
custom `Function`-interface (and its associated JSON-file) below! Also,
check out the [firstlevel-analysis](/Porcupine/examples/firstlevel-example)
and [FEAT-reconstruction](/Porcupine/examples/FEAT-example) examples from
our gallery to check out real use-cases of custom module in Porcupine!

[<i class="fa fa-download"></i> Download script][1]{: .btn}
[<i class="fa fa-download"></i> Download .py-file][2]{: .btn}
[<i class="fa fa-download"></i> Download .JSON][3]{: .btn}

[1]:https://raw.githubusercontent.com/TimVanMourik/Porcupine/master/utilities/parse_custom_module.py
[2]:{{ site.url }}{{ site.baseurl }}/documentation/custom/example_custom_module.py
[3]:{{ site.url }}{{ site.baseurl }}/documentation/custom/example_custom_module.JSON
