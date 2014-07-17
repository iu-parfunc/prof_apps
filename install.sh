#!/bin/bash

ZCA_BUILD='../zcatoggle/build';
DYN_BUILD='../dynaprof/build';
GZIP_HOME='gzip-1.6';
GREP_HOME='grep-2.18';
PBZIP2_HOME='pbzip2-1.1.8';
MCF_HOME='mcf-1.3'
PERL_HOME='perl-5.8.7'
H264_HOME='h264ref-9.3'

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
  pbzip2)  
    cp $ZCA_BUILD/* $PBZIP2_HOME/instrumented
    cp $DYN_BUILD/* $PBZIP2_HOME/instrumented
    cp $DYN_BUILD/../src/dynaprof.h $PBZIP2_HOME/instrumented
    ;;
  mcf)
    cp $ZCA_BUILD/* $MCF_HOME/instrumented
    cp $DYN_BUILD/* $MCF_HOME/instrumented
    cp $DYN_BUILD/../src/dynaprof.h $MCF_HOME/instrumented 
    ;;

  perl)
    cp $ZCA_BUILD/* $PERL_HOME/instrumented
    cp $DYN_BUILD/* $PERL_HOME/instrumented
    cp $DYN_BUILD/../src/dynaprof.h $PERL_HOME/instrumented 
    ;;

  h264)
    cp $ZCA_BUILD/* $H264_HOME/instrumented
    cp $DYN_BUILD/* $H264_HOME/instrumented
    cp $DYN_BUILD/../src/dynaprof.h $H264_HOME/instrumented
    ;;

  *) echo "Unknown benchmark"
    ;;
esac

