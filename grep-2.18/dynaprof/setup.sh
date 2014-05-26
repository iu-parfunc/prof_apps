#!/bin/bash

BENCH_HOME=`pwd`
BUILD_HOME=`pwd`/../../../
ZCA_SRC=$BUILD_HOME/zcatoggle/src
DYN_SRC=$BUILD_HOME/dynaprof/src

if [ -d "../instrumented" ]; then
  rm -rf ../instrumented
fi

echo -e "Building dynaprof.."
cd $ZCA_SRC
make clean
make
cd $DYN_SRC
make clean
make

cd $BENCH_HOME
cp -R ../original ../instrumented
chmod u+x ../../install.sh
cd ../../
./install.sh grep

echo -e "\nInstalled dynaprof..."



