#!/bin/bash

BUILD_HOME=`pwd`/../..
GZIP_HOME=`pwd`
ZCA_SRC=$BUILD_HOME/zcatoggle/src
DYN_SRC=$BUILD_HOME/dynaprof/src

echo -e "\n========================="
echo -e "Running without profiling"
echo -e "========================="

if [ -d "instrumented" ]; then
   rm -rf instrumented
fi

cp -R original/ instrumented/
cd instrumented

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

echo -e "\n========================="
echo -e "Running with dynaprof    "
echo -e "========================="

cp -R original/ instrumented/

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

echo -e "\n========================="
echo -e "Running with gprof       "
echo -e "========================="

cp -R original/ instrumented/
cd instrumented

echo -e "Building gzip with gprof enabled..."
autoreconf
./configure CC=gcc CFLAGS='-pg'
make

echo -e "\nRunning gzip..."
(time ./gzip -c ../../resources/a > a.gz) 2> ../gprof_time
gprof gzip gmon.out > ../gprof.out
cd ..

echo -e "Cleaning up..."
rm -rf instrumented

echo -e "Done..."

mkdir instrumented # This is to prevent errors when library artifacts being copied to other subsequent benchmarks

