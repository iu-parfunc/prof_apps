#!/bin/bash

set -e

if [ -d "../instrumented" ]; then
  rm -rf ../instrumented
fi

cp -R ../original/ ../instrumented/
