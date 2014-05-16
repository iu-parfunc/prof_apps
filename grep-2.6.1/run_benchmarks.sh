#!/bin/bash

BUILD_HOME=`pwd`/../..
GREP_HOME=`pwd`
ZCA_SRC=$BUILD_HOME/zcatoggle/src
DYN_SRC=$BUILD_HOME/dynaprof/src

echo -e "\n========================="
echo -e "Running without profiling"
echo -e "========================="

cp -R original/ instrumented/
cd instrumented

echo -e "Building grep..."
autoreconf
./configure CC=gcc
make

echo -e "\nRunning grep..."
cd src
(time ./grep -rl test . > /dev/null) 2> ../../original_time
cd ../..

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
cd $GREP_HOME
cd instrumented
autoreconf
./configure CC=icc LIBS='libdynaprof.a libzca-toggle.a -lelf' CFLAGS='-O0'
make

echo -e "\nInstrumenting ..."
cd ..; ./instrument.sh

echo -e "\nBuilding grep with instrumentation..."
cd instrumented
make clean
make

echo -e "\nRunning instrumented binary..."
cd src
(time ./grep -rl test . > /dev/null) 2> ../../dynaprof_time
cp prof.out ../..
cd ../..

echo -e "\nCleaning up..."
rm -rf instrumented

echo -e "\nDone..."

echo -e "\n========================="
echo -e "Running with gprof       "
echo -e "========================="

cp -R original/ instrumented/
cd instrumented

echo -e "Building grep with gprof enabled..."
autoreconf
./configure CC=gcc CFLAGS='-pg'
make

echo -e "\nRunning grep..."
cd src
(time ./grep -rl test . > /dev/null) 2> ../../gprof_time
gprof grep gmon.out > ../../gprof.out
cd ../..

echo -e "Cleaning up..."
rm -rf instrumented

echo -e "Done..."

