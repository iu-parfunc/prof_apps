#!/bin/bash

if [ -d "../instrumented" ]; then
  rm -rf ../instrumented
fi

cp -R ../original ../instrumented
cp make ../instrumented/Makefile
