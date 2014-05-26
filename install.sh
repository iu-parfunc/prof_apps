#!/bin/bash

ZCA_BUILD='../zcatoggle/build';
DYN_BUILD='../dynaprof/build';
GZIP_HOME='gzip-1.6';
GREP_HOME='grep-2.18';

case "$1" in

  gzip)  
    cp $ZCA_BUILD/* $GZIP_HOME/instrumented
    cp $DYN_BUILD/* $GZIP_HOME/instrumented
    cp $DYN_BUILD/../src/dynaprof.h $GZIP_HOME/instrumented
    ;;
  grep)  
    cp $ZCA_BUILD/* $GREP_HOME/instrumented
    cp $ZCA_BUILD/* $GREP_HOME/instrumented/src
    cp $DYN_BUILD/* $GREP_HOME/instrumented
    cp $DYN_BUILD/* $GREP_HOME/instrumented/src
    cp $DYN_BUILD/../src/dynaprof.h $GREP_HOME/instrumented
    cp $DYN_BUILD/../src/dynaprof.h $GREP_HOME/instrumented/src
    ;;
  *) echo "Unknown benchmark"
    ;;
esac

