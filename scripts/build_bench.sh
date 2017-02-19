#!/bin/bash

SEQ_BENCHES=( "bzip-1.0.3" "h264ref-9.3" "hmmer" "perl-5.8.7" "sjeng" )
PAR_BENCHES=( "blackscholes" "fluid" "hull" "nbody" ) 

mode="seq"

function build {
  root=`pwd`
  if [ $mode = "seq" ]
  then
    echo -e "--------------------------------------------"
	  echo -e " Building Sequential Application Benchmarks "
	  echo -e "--------------------------------------------\n"

    for bench in "${SEQ_BENCHES[@]}"
    do
      echo -e "-------------- Building $bench --------------- \n"
      (cd $root/$bench/liteprof;make build)
      echo -e "\n"
    done
  else
     echo -e "--------------------------------------------"
 	   echo -e " Building Parallel Application Benchmarks "
     echo -e "--------------------------------------------\n"

     for bench in "${PAR_BENCHES[@]}"
     do
       echo -e "-------------- Building $bench --------------- \n"
       (cd $root/$bench/liteprof;make build)
      echo -e "\n"
     done
  fi
}

while [ $# -gt 0 ]
do
  case "$1" in
    -s)  mode="seq";;
    -p)  mode="par";;
    --)  shift; break;;
    -*)
         echo >&2 \
         "usage: $0 [-s] [-p]"
         exit 1;;
    *)  break;;    # terminate while loop
  esac
  shift
done

build
