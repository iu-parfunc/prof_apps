#!/bin/bash

set -xe

ORIG=sources
PARSE=cparse
INSTRUMENT=tau_instrumentor
OPTS='-Wall -Winline -DSPEC_CPU -DPERL_CORE -DSPEC_CPU_LP64 -DSPEC_CPU_LINUX_X64'

cd $ORIG/
SRC=`find ./ -name "*.c" -o -name "*.cpp"`
HDRS=`find ./ -name "*.h" -o -name "*.hpp" -o -name "*.hin"`
cd ..

for path in $HDRS; do
  dirnm=`dirname $path`
  cp -v ./$ORIG/$path ./instrumented/$dirnm/
done

for path in $SRC; do 
  dirnm=`dirname $path`
  filenm=`basename $path`
  fn="${filenm%.*}"
  cp -v ./$ORIG/$path ./instrumented/$dirnm/
  $PARSE ./instrumented/$path -I./instrumented $OPTS -o ./instrumented/$dirnm/$fn.pdb   
  $INSTRUMENT ./instrumented/$dirnm/$fn.pdb ./instrumented/$path -l -o ./instrumented/$dirnm/$fn.tau.c \
               -c -spec ./TAUINST.SPEC
  mv ./instrumented/$dirnm/$fn.tau.c ./instrumented/$path
done

rm -f ./instrumented/$dirnm/*.pdb
