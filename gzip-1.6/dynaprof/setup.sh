#!/bin/bash

BENCH_HOME=`pwd`
ZCA_SRC='../../../zcatoggle/src'
DYN_SRC='../../../dynaprof/src'

if [ -d "../instrumented" ]; then
  rm -rf ../instrumented
fi

if [ ! -e ../../resources/a ]; then
  cd ../../resources
  chmod u+x filegen
  ./filegen
  cd ../gzip-1.6/gprof
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
./install.sh gzip

echo -e "\nInstalled dynaprof..."



