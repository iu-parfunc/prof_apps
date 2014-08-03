#!/bin/bash

set -e 

if [ -d "../instrumented" ]; then
  rm -rf ../instrumented
fi

if [ ! -e ../../resources/a ]; then
  cd ../../resources
  chmod u+x filegen
  ./filegen
  cd ../gzip-1.6/unprofiled
fi

cp -R ../original/ ../instrumented/
