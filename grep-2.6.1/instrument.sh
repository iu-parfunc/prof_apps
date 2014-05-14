#!/bin/bash

set -e
# set -x
ORIG=sources
PARSE=cparse
INSTRUMENT=tau_instrumentor

cd $ORIG/
SRC=`find ./ -name "*.c"`
cd ..

for path in $SRC; do 
  dirnm=`dirname $path`
  filenm=`basename $path`
  fn="${filenm%.*}"
  cp -v ./$ORIG/$path ./instrumented/$dirnm/
  $PARSE ./instrumented/$path -o ./instrumented/$dirnm/$fn.pdb   
  $INSTRUMENT ./instrumented/$dirnm/$fn.pdb ./instrumented/$path -l -o ./instrumented/$dirnm/$fn.tau.c \
               -c -spec ./TAUINST.SPEC
  mv ./instrumented/$dirnm/$fn.tau.c ./instrumented/$path
done

rm ./instrumented/$dirnm/*.pdb
