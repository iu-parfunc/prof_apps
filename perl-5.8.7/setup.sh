#!/bin/bash

set -e 

if [[ -d "instrumented" ]]; then
  rm -rf instrumented
fi

cp -R original instrumented

if [[ $1 == "liteprof" ]]; then
  cp liteprof/perlmain.c instrumented/perlmain.c
fi
