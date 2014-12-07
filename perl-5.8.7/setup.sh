#!/bin/bash

set -e

BENCH_HOME=`pwd`

if [ -d "instrumented" ]; then
  rm -rf instrumented
fi

cp -R original instrumented
