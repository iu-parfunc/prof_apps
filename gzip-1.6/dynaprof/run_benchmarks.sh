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
echo -e "Running with dynaprof    "
echo -e "========================="

cp -R ../original/ ../instrumented/

echo -e "Building dynaprof...\n"
cd $ZCA_SRC
make clean
make
cd $DYN_SRC
make clean
make

echo -e "\nInstalled dynaprof..."
cd $GZIP_HOME
cd instrumented
autoreconf
./configure CC=icc LIBS='libdynaprof.a libzca-toggle.a -lelf' CFLAGS='-O0'
make

echo -e "\nInstrumenting gzip..."
cd ..; ./instrument.sh

echo -e "\nBuilding gzip with instrumentation..."
cd instrumented
make clean
make

echo -e "\nRunning instrumented binary..."
(time ./gzip -c ../../resources/a > a.gz) 2> ../dynaprof_time
cp prof.out ..
cd ..

echo -e "\nCleaning up..."
rm -rf instrumented

echo -e "\nDone..."

mkdir instrumented # This is to prevent errors when library artifacts being copied to other subsequent benchmarks

