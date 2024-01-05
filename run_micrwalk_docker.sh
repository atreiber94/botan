#!/bin/sh
LIBRARY="$(pwd)"

sudo docker run -it -v $LIBRARY:/mw/library microwalk/microwalk-pin /bin/bash
