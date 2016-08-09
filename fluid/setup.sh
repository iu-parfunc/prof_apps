#!/bin/bash

set -e 

if [[ $1 == "liteprof" ]]; then
  cp liteprof/pthread.cpp src/pthread.cpp
fi
