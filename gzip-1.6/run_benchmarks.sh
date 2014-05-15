#!/bin/bash

BUILD_HOME=`pwd`/../..
GZIP_HOME=`pwd`
ZCA_SRC=$BUILD_HOME/zcatoggle/src
DYN_SRC=$BUILD_HOME/dynaprof/src

echo -e "\n========================="
echo -e "Running without profiling"
echo -e "========================="

cp -R original/ instrumented/
cd instrumented

echo -e "Building gzip with instrumentation..."
./configure CC=gcc
make

echo -e "Running gzip..."
time (./gzip -c ../../resources/a > a.gz) > ../original_time
cd ..

echo -e "Cleaning up..."
rm -rf instrumented

echo -e "Done..."

echo -e "\n========================="
echo -e "Running with dynaprof    "
echo -e "========================="

cp -R original/ instrumented/

echo -e "Building dynaprof..."
cd $ZCA_SRC
make clean
make
cd $DYN_SRC
make clean
make

echo -e "Installed dynaprof..."
cd $GZIP_HOME
cd instrumented
autoreconf
./configure CC=icc LIBS='libdynaprof.a libzca-toggle.a -lelf' CFLAGS='-O0'
make

echo -e "Instrumenting gzip..."
cd ..; ./instrument.sh

echo -e "Building gzip with instrumentation..."
cd instrumented
make

echo -e "Running instrumented binary..."
time (./gzip -c ../../resources/a > a.gz) > ../dynaprof_time
cp prof.out ..
cd ..

echo -e "Cleaning up..."
rm -rf instrumented

echo -e "Done..."

echo -e "\n========================="
echo -e "Running with gprof       "
echo -e "========================="

cp -R original/ instrumented/
cd instrumented

echo -e "Building gzip with gprof enabled..."
./configure CC=gcc CFLAGS='-pg'
make

echo -e "Running gzip..."
time (./gzip -c ../../resources/a > a.gz) > ../gzip_time
gprof gzip gmon.out > ../gprof.out
cd ..

echo -e "Cleaning up..."
rm -rf instrumented

echo -e "Done..."

