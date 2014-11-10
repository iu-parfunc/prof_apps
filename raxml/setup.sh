#!/bin/bash

set -e

BENCH_HOME=`pwd`

if [ -d "instrumented" ]; then
  rm -rf instrumented
fi

cd $BENCH_HOME
cp -R original instrumented
