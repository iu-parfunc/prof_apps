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

echo -e "Building dynaprof...\n"
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
./install.sh pbzip2

echo -e "\nInstalled dynaprof..."



