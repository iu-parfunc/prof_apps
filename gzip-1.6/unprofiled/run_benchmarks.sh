#!/bin/bash

BUILD_HOME=`pwd`/../../..
GZIP_HOME=`pwd`/..
ZCA_SRC=$BUILD_HOME/zcatoggle/src
DYN_SRC=$BUILD_HOME/dynaprof/src

if [ -d "../instrumented" ]; then
  rm -rf ../instrumented
fi

if [ ! -e ../../resources/a ]; then
  cd ../../resources
  chmod u+x filegen
  ./filegen
  cd ../gzip-1.6/gprof
fi

echo -e "\n========================="
echo -e "Running without profiling"
echo -e "========================="

if [ -d "../instrumented" ]; then
  rm -rf ../instrumented
fi

cp -R ../original/ ../instrumented/
cd ../instrumented

echo -e "Building gzip..."
autoreconf
./configure CC=gcc
make

echo -e "\nRunning gzip..."
(time ./gzip -c ../../resources/a > a.gz) 2> ../original_time
cd ..

echo -e "Cleaning up..."
rm -rf instrumented

echo -e "Done..."

mkdir instrumented # This is to prevent errors when library artifacts being copied to other subsequent benchmarks

