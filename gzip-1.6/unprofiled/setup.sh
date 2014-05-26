#!/bin/bash

if [ -d "../instrumented" ]; then
  rm -rf ../instrumented
fi

if [ ! -e ../../resources/a ]; then
  cd ../../resources
  chmod u+x filegen
  ./filegen
  cd ../gzip-1.6/gprof
fi

cp -R ../original/ ../instrumented/
