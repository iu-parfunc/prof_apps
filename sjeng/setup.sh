#!/bin/bash

set -e 

if [[ -d "instrumented" ]]; then
  rm -rf instrumented
fi

cp -R original instrumented

if [[ $1 == "liteprof" ]]; then
  cp liteprof/sjeng.c instrumented/sjeng.c
fi
