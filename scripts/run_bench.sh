#!/bin/bash

SEQ_BENCHES=( "bzip-1.0.3" "h264ref-9.3" "hmmer" "perl-5.8.7" "sjeng" )
PAR_BENCHES=( "blackscholes" "fluid" "hull" "nbody" ) 

EXPERIMENTS=( "Layout_Distribution-Table2" "Init_Costs-Table6" )

mode="seq"

function run {
  pwd="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
  root=$pwd/..
  if [ $mode = "seq" ]
  then
    echo -e "--------------------------------------------"
	  echo -e " Running Sequential Application Benchmarks "
	  echo -e "--------------------------------------------\n"

    for bench in "${SEQ_BENCHES[@]}"
    do
      echo -e "----------- Running $bench -------------\n"
      (cd $root/$bench/liteprof;make run)
      echo -e "\n"
    done
  else
     echo -e "--------------------------------------------"
 	   echo -e " Running Parallel Application Benchmarks "
     echo -e "--------------------------------------------\n"

     for bench in "${PAR_BENCHES[@]}"
     do
       echo -e "----------- Running $bench ------------\n"
       (cd $root/$bench/liteprof;make run)
      echo -e "\n"
     done
  fi
}

function collect {
  pwd="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
  bench_root=$pwd/..
  toplvl=$bench_root/../..

  for exp in "${EXPERIMENTS[@]}"
  do
    for bench in "${SEQ_BENCHES[@]}"
    do
      yes | cp -f $bench_root/$bench/instrumented/layouts.out $toplvl/results/$exp/raw/$bench
      echo -e "\n"
    done
  done
}

function init {
  pwd="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
  bench_root=$pwd/..
  toplvl=$bench_root/../..

  mkdir -p $toplvl/results

  for exp in "${EXPERIMENTS[@]}"
  do
    mkdir -p $toplvl/results/$exp
    mkdir -p $toplvl/results/$exp/raw/
  done
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

init
(export PROF_TYPE="NOPROF" ; run)
collect
