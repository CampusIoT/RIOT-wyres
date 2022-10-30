#!/bin/bash

# From https://mynewt.apache.org/v1_10_0/get_started/docker.html

if [ "$1" = "debug" ] || [ "$1" = "run" ]
then
    ti="-ti"
fi

docker run -e NEWT_USER=$(id -u) -e NEWT_GROUP=$(id -g) -e NEWT_HOST=$(uname) $ti --rm --device=/dev/bus/usb --privileged -v $(pwd):/workspace -w /workspace mynewt/newt:latest /newt "$@"
