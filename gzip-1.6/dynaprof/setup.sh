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
case "$1" in

  direct_05)
    make OVERHEAD="-DOVERHEAD_5" STRATEGY="-DDIRECT_UPDATE_STRATEGY"
    ;;
  direct_10)
    make OVERHEAD="-DOVERHEAD_10" STRATEGY="-DDIRECT_UPDATE_STRATEGY"
    ;;
  direct_25)
    make OVERHEAD="-DOVERHEAD_25" STRATEGY="-DDIRECT_UPDATE_STRATEGY"
    ;;
  direct_50)
    make OVERHEAD="-DOVERHEAD_50" STRATEGY="-DDIRECT_UPDATE_STRATEGY"
    ;;
  empty)
    make STRATEGY="-DEMPTY_STRATEGY"
    ;;
  *);;
esac

cd $BENCH_HOME
cp -R ../original ../instrumented
chmod u+x ../../install.sh
cd ../../
./install.sh gzip

echo -e "\nInstalled dynaprof..."



