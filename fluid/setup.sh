#!/bin/bash

set -e 

if [[ $1 == "liteprof" ]]; then
  cp liteprof/pthreads.cpp src/pthreads.cpp
fi
