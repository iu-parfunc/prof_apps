#!/bin/bash

set -e

echo "Starting instrumentation, current dir `pwd`."

ROOT=`pwd`
ORIG=$ROOT/sources
DEST=$ROOT/instrumented
PARSE=cparse
INSTRUMENT=tau_instrumentor
OPTS='-Wall -Winline -DSPEC_CPU -DPERL_CORE -DSPEC_CPU_LP64 -DSPEC_CPU_LINUX_X64'

cd $ORIG
SRC=`find ./ -name "*.c" -o -name "*.cpp"`
HDRS=`find ./ -name "*.h" -o -name "*.hpp" -o -name "*.hin"`
cd $ROOT

# echo "Instrumenting SRC: $SRC"
# echo "Instrumenting with HDRS: $HDRS"

for path in $HDRS; do
  dirnm=`dirname $path`
  cp -v $ORIG/$path $DEST/$dirnm/
done

for path in $SRC; do 
  dirnm=`dirname $path`
  filenm=`basename $path`
  fn="${filenm%.*}"
  pwd
  cp -v $ORIG/$path $DEST/$dirnm/
  set -x 
  $PARSE $DEST/$path -I$DEST $OPTS -o $DEST/$dirnm/$fn.pdb   
  $INSTRUMENT $DEST/$dirnm/$fn.pdb $DEST/$path -l -o $DEST/$dirnm/$fn.tau.c \
               -c -spec ./TAUINST.SPEC
  mv $DEST/$dirnm/$fn.tau.c $DEST/$path
  set +x
done

rm -f $DEST/$dirnm/*.pdb
