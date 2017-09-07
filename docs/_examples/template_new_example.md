#---
#title: "Short name of your pipeline"
#excerpt: "Short description of your pipeline!"
#header:
#  teaser: /examples/example_pipelines/name_of_your_example_directory/file_with_picture_for_thumbnail.png
#layout: single
#permalink: /examples/a-short-name-of-your-workflow
#---

FIRST, UNCOMMENT THE PREAMBLE ABOVE (we did this to make sure this template wasn't added to the gallery)

SET THE PATH BELOW (example_path) CORRECTLY.

{% assign example_path = 'examples/example_pipelines/name_of_your_example_directory/' %}

WRITE A SHORT DESCRIPTION OF YOUR PIPELINE HERE.

OPTIONAL: ADD AN IMAGE OF YOUR WORKFLOW EDITOR BELOW BY CHANGING THE NAME
(porcupine_graph.png) ACCORDINGLY

<figure>
	<a href="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_graph.png"><img
    src="{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_graph.png"></a>
	<figcaption>Write a caption for your figure</figcaption>
</figure>

LEAVE THE TEXT BELOW AS-IS

Check out the Porcupine-generated Python-script, Porcupine-pipeline, and
associated Dockerfile in our [Github repository](https://github.com/TimVanMourik/Porcupine/tree/example_workflows/docs/_{{ example_path }}) or download the files directly below.

REMOVE THE BUTTONS BELOW IF YOU DON'T PROVIDE THE CORRESPONDING FILE
(e.g. IF YOU DON'T INCLUDE A DOCKERFILE FOR EXAMPLE)

[<i class="fa fa-download"></i> Download .pork-file][1]{: .btn}
[<i class="fa fa-download"></i> Download .py-file][2]{: .btn}
[<i class="fa fa-download"></i> Download Dockerfile][3]{: .btn}

MAKE SURE THE NAMES BELOW (porcupine_pipeline.pork etc.) CORRESPOND TO THE ACTUAL
NAMES OF YOUR FILES.

[1]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_pipeline.pork
[2]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/porcupine_generated_workflow.py
[3]:{{ site.url }}{{ site.baseurl }}/{{ example_path }}/Dockerfile

YOU'RE DONE! MAKE SURE TO REMOVE THESE INSTRUCTIONS (BASICALLY ANYTHING IN FULL-CAPS)
