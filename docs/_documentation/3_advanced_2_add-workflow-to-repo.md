---
title: "Add your own workflow to our gallery"
excerpt: "How to contribute to our piggy bank of .pork files"
layout: single
author_profile : false
categories:
  - 3. Advanced usage
permalink: /documentation/advanced/contributing
---

We'd love to add your custom Porcupine pipeline to our website! To do so,
please follow these instructions.

## Step 1: fork our repository
We serve this website using [Github pages](https://pages.github.com/), so adding
content is as easy as modifying content in the `docs/` folder of our repository
([https://github.com/TimVanMourik/Porcupine](https://github.com/TimVanMourik/Porcupine)).

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/assets/images/fork_porcupine.png"><img
    src="{{ site.url }}{{ site.baseurl }}/assets/images/fork_porcupine.png"></a>
	<figcaption>Fork Porcupine on Github.</figcaption>
</figure>

## Step 2: add a new directory with our files
Then, add a directory in the `docs/_examples/example_pipelines` directory with
a sensible name (like "freesurfer_recon_all_example"). Make sure to add the following
files to that directory:

1. Your `.pork` file containing your Porcupine-pipeline
2. Your `.py` file with the Porcupine-generated Python code (optional)
3. The associated Dockerfile (optional)
4. Custom Python modules (if you used them) in both `JSON` and `.py` format (optional)
5. A screenshot or SVG-exported image of your workflow editor (so that we can use it as a thumbnail in our gallery!)

## Step 3: add a new markdown file describing your pipeline
After creating a directory with the files listed above, you only need to
create a markdown-file in which you shortly describe your pipeline and list
the download links of your files. We've written a template for you, such that
you only have to adapt some of the text in there! This template is located
at `docs/_examples/template_new_example`; just copy its contents in a new
file, which should be located at `docs/_examples/your_pipeline.md`. Give it
a sensible name (like "10_freesurfer_recon_example"), in which you start the
filename with a number (which should follow the order of the already existing
example markdown files, to preserve order in the gallery).

Thus, suppose that you want to add your "freesurfer recon-all pipeline". Then
the `docs/_examples` directory of your Porcupine-fork should look similar to
the following:

```
_examples
├── 1_simple_example.md
...
├── 7_FEAT_example.md
├── 8_freesurfer_reconall_example.md
└── example_pipelines
    └── freesurfer_recon_all_example
        ├── Dockerfile
        ├── your_pork_file.pork
        ├── porcupine_generated_pipeline.py
        ├── mycustommodule.py
        ├── mycustommodule.JSON
        └── image_of_your_workflow_editor.png
```

## Step 4: send us a pull-request!
Once you've added the directory with your files and added a markdown-file
(based on the provided template), you can simply send us a pull-request on Github
and we'll merge it into our repository as soon as possible!

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/assets/images/PR_porcupine.png"><img
    src="{{ site.url }}{{ site.baseurl }}/assets/images/PR_porcupine.png"></a>
	<figcaption>Send us a pull request on Github.</figcaption>
</figure>
