#!/bin/bash

set -e
# set -x
ORIG=orig-2.6.1

cd $ORIG/
SRC=`find ./ -name "*.c"`
cd ..

for path in $SRC; do 
  dirnm=`dirname $path`
  cp -v ./$ORIG/$path ./instrumented/$dirnm/
done

