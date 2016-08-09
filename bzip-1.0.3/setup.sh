#!/bin/bash

set -e

BENCH_HOME=`pwd`

if [ -d "instrumented" ]; then
  rm -rf instrumented
fi

if [ ! -e ../resources/a ]; then
  cd ../resources
  chmod u+x filegen
  ./filegen
fi

cd $BENCH_HOME
cp -R original instrumented

if [[ $1 == "liteprof" ]]; then
  cp liteprof/spec.c instrumented/spec.c
fi
