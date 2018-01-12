---
title: "Developer's Guide"
excerpt: "For developers that want to extend Porcupine"
layout: single
author_profile : false
categories:
  - 4. Developers
permalink: /documentation/developers/guide
---

Porcupine is designed to be largely agnostic about the package for which you are
programming. Here it is important that all functions within the package behave
consistently and have a standard way of dealing with input and output arguments.
If it does that, it should be possible to define a way of transforming your
nodes into code for Python, MATLAB, bash or your own weapon of choice. It will
however require some small amount of C++ programming. We here eplain how you
can easily write your own code generator. The process consists of three parts:

- Creating a new generator .cpp and .hpp file.
- Registering the code in the main application
- If you want, add syntax highligthing for the code

In the next sections, we will walk you through this process.
