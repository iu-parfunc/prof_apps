#!/bin/bash
# Common setup tasks shared between the different "variant" subdirectories:

set -e
set -x
DEST=original/ref/input/swiss41

if ! [ -f $DEST ]; then
  wget http://html.soic.indiana.edu/~parfunc/datasets/hmmer/swiss41.gz
  gunzip swiss41.gz
  mv swiss41 $DEST
fi
