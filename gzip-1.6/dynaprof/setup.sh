#!/bin/bash

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

cd $BENCH_HOME
cp -R ../original ../instrumented
chmod u+x ../../install.sh
cd ../../
./install.sh gzip

echo -e "\nInstalled dynaprof..."



