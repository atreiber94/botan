#!/bin/sh
LIBRARY="$(pwd)"

docker run -v $LIBRARY:/mw/library ghcr.io/microwalk-project/microwalk:pin sh -c "cd ../library/microwalk && ./build.sh && ./analyze.sh"
