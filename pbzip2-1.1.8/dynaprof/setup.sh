#!/bin/bash

set -e

BENCH_HOME=`pwd`
BUILD_HOME=`pwd`/../../../
ZCA_SRC=$BUILD_HOME/zcatoggle/src
DYN_SRC=$BUILD_HOME/dynaprof/src

if [ -d "../instrumented" ]; then
  rm -rf ../instrumented
fi

if [ ! -e ../../resources/a ]; then
  cd ../../resources
  chmod u+x filegen
  ./filegen
fi

cp -R ../original ../instrumented
cp make ../instrumented/Makefile
cp ../sources/*.cpp ../instrumented

chmod u+x ../../install.sh
cd ../../
./install.sh pbzip2

echo -e "\nInstalled dynaprof..."



