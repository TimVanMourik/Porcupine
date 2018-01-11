---
title: "Using Dockerfiles"
excerpt: "How build and use Porcupine-generated Dockerfiles"
layout: single
author_profile : false
categories:
  - 1. Basics
permalink: /documentation/basics/building-dockerfiles
---

As explained briefly in the [section on the code editor](/Porcupine/documentation/basics/code-editor),
Porcupine also generates a *Dockerfile* next to the Python script containing code
for your Nipype-pipeline (based on the awesome work of the [neurodocker package](https://github.com/kaczmarj/neurodocker)).
This Dockerfile specifies the "recipe" to build a "Docker-image"
that specifies the run-environment (in terms of software dependencies and
environment variables) necessary to execute your pipeline.

Thus, a docker-image based on the Porcupine-generated Dockerfile in combination
with the Porcupine-generated Python-script make sure your analysis is
*completely reproducible* as it provides both your analysis as well as its
necessary run-environment.

### How does Porcupine generate Dockerfiles?
Essentially, Porcupine checks which software packages you leverage in your
pipeline. For example, if you build a skullstripping pipeline for structural
MRI data that depends on `AFNI`, `ANTs`, and `FSL` (like [this one](/Porcupine/examples/skullstrip-example)),
then Porcupine makes sure that the installation of these packages are specified
in the Dockerfile. In addition to the necessary underlying neuroimaging software-packages,
Porcupine-generated Dockerfiles obviously also contain Nipype (and its dependencies)
itself.

### How to build your Docker-image using your Dockerfile
As explained before, Dockerfiles are like "recipes" for Docker-images.
Therefore, to create a Docker-image (i.e., the run-environment/image itself) you
need to "build" it from the Dockerfile. To do this, you obviously need to have
Docker installed (check their [installation page](https://docs.docker.com/engine/installation/)
for instructions).

Before you build your Dockerfile, though, you need to modify the Porcupine-generated
Dockerfile slightly. This is because the Dockerfile should know where your
Python script is saved and how it is named. We recommend saving the Python-script
in the same directory of your Dockerfile and giving it a descriptive name
(like `skullstripping_pipeline.py`). Thus, your directory should look something
like this:

```
~/skullstripping_analysis/
├── Dockerfile
└── skullstripping_pipeline.py
```

Given that you've organized your files in a directory-structure as above,
you need to change the following two lines of the Dockerfile (all the way at the bottom) ...

```
ADD /path/to/pipeline/script.py /somewhere/porcupipeline.py
CMD ["python", "/somewhere/porcupipeline.py"]
```

... into the following:

```
ADD ./skullstripping_analysis.py /skullstripping_analysis.py
CMD ["python", "/skullstripping.py"]
```

Now, building your custom Docker-file is as easy as running the following command
(make sure you're in the directory with your files, e.g. the `~/skullstrip_analysis`
directory from the example above):

```
$ docker build -t skullstripimage -f Dockerfile .
```

Here, the `-t` flag specifies the name of your image and the `-f` flag specifies
the Dockerfile that you want to use to build your image.

**Beware**: Installing FSL in Docker images causes the image to become very large
(>10GB), which may cause an error on Mac OS and Windows due to size restrictions
("No space left on device" error). Check [this post](https://forums.docker.com/t/increase-docker-container-disk-space-on-os-x/26725/2)
 on how to increase disk space for the Docker container.
{: .notice--warning}

### Running your docker-image!
Once you've built your docker-image, it's easy to actually run it. To do so,
run the following in your terminal:

```
$ docker run --rm skullstripimage
```

(The `--rm` flag ensures that Docker will "clean up" the image-filesystem after
running your image.)

### File I/O when using Docker
When you intend do build a Docker-image to share your analyses with others,
you have to make sure that your pipeline is adapted to running in a Docker container.
To do so, you usually only need to make sure that Docker can access the data
intended to be processed by your pipeline and that it can return the output
of the pipeline correctly. The easiest way is to mount the local directory containing
your data onto the docker-image and, additionally, mount the directory to which
the outputs of your pipeline are written onto your local filesystem.

Mounting directories are achieved with the `-v` flag in the `docker run` command,
which should be followed by a command in the format of `localdir:dockerdir[:permissions]`.

Suppose that we have a (preferably BIDS-formatted!) data-set to apply our
skullstrip-pipeline to, which we store locally next to our `skullstrip_analysis`
directory in a directory named `bids_data`:

```
~/
├── bids_data
│   ├── sub-01
│   │   ├── anat
│   │   │   └── sub-01_T1w.nii.gz
│   │   └── func
│   │       ├── sub-01_task-nback_bold.nii.gz
│   │       └── sub-01_task-nback_events.tsv
│   └── sub-02
│       ├── anat
│       │   ├── sub-02_T1w_brain.nii.gz
│       │   ├── sub-02_T1w.nii.gz
│       │   └── sub-02_T1w_warpcoef.nii.gz
│       └── func
│           ├── sub-02_task-nback_bold.nii.gz
│           └── sub-02_task-nback_events.tsv
└── skullstripping_analysis
    ├── Dockerfile
    └── skullstripping_pipeline.py
```

Then, to mount the `~/bids_data` directory to the docker-image at the location
`/data`, we simply run the docker image as:

```
$ docker run --rm -v ~/bids_data:/data:ro skullstripimage
```

Now, your pipeline can access the your data from the local `~/bids_data`
directory at `/data` inside the docker-image (with *read-only* permissions,
which we set using `:ro`)!

**Important**: Make sure your pipeline is adapted to running in a docker-image.
Most of the times, you only have to adapt your file I/O operations such that
they read/write files from the appropriate location. For example, in the above
example, make sure your node that grabs data from disk (using the `SelectFiles`
or `DataGrabber` interfaces, for example) points at the `/data` directory,
and not the `~/bids_data` directory!
{: .notice--warning}

In addition to mapping our input-data to the docker-images, we would like to get the outputs of the
pipeline running in the docker-image on our local drive as well, so we need another
mount. Suppose the pipeline writes the pipeline-results to the `/pipeline_outputs`
directory in the docker-image (through a `DataSink` node at the end of the pipeline).
We can then mount this docker directory to our local drive (let's say to the local
directory `~/outputs_from_pipeline`) as follows:

```
$ docker run --rm -v ~/bids_data:/data:ro -v ~/outputs_from_pipeline:/pipeline_outputs skullstripimage
```

Please note that, also when mounting the output-directory, you need to first
specify the local directory and then the docker-directory.

Then, when running the above docker run command, all outputs from the docker-directory
`/pipeline_outputs` will also locally appear at `~/outputs_from_pipeline`!

### Making a BIDS-app from your pipeline
This section was dedicated to showing how to build a Docker-image that complements
your analysis, such that others can reproduce it. Another use of the Porcupine-generated
Dockerfile is that you can use it to easily build a [BIDS-app](http://bids-apps.neuroimaging.io/)
based on your pipeline! Currently, you need to manually wrap your Porcupine-generated
Python-script in another "run-script" that provides the command-line arguments
that a proper BIDS-app requires. We are working on automating this step in Porcupine,
but for the time being, check out the [documentation section](/Porcupine/documentation/advanced/make-a-bids-app)
on building BIDS-apps.
