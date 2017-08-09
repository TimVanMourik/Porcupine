#!/bin/bash
xhost local:root
docker run -it -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY timvanmourik/porcupine:latest ./bin/Porcupine