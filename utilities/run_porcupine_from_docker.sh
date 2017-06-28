#!/bin/bash
xhost local:root
docker run docker run -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY porcupine
