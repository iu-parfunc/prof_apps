#!/bin/bash

set -e
# set -x
ORIG=original
PARSE=cparse
INSTRUMENT=tau_instrumentor

cd $ORIG/
SRC=`find ./ -name "*.c"`
HDRS=`find ./ -name "*.h"`
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
  $PARSE ./instrumented/$path -I./instrumented/lib/ -o ./instrumented/$dirnm/$fn.pdb   
  $INSTRUMENT ./instrumented/$dirnm/$fn.pdb ./instrumented/$path -l -o ./instrumented/$dirnm/$fn.tau.c \
               -c -spec ./TAUINST.SPEC
  mv ./instrumented/$dirnm/$fn.tau.c ./instrumented/$path
done

rm ./instrumented/$dirnm/*.pdb
