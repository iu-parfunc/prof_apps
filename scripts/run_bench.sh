#!/bin/bash

SEQ_BENCHES=( "bzip-1.0.3" "h264ref-9.3" "hmmer" "perl-5.8.7" "sjeng" )

declare -A PAR_BENCHES=( ["blackscholes"]="src" ["fluid"]="src" ["hull"]="quickHull" ["nbody"]="BarnesHut" )
declare -A EXPERIMENTS=( ["Layout_Distribution-Table2"]="layouts.out" ["Init_Costs-Table6"]="stats.out" ["Mem_Util-Table5"]="stats.out" )

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

     for bench in "${!PAR_BENCHES[@]}"
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

  for exp in "${!EXPERIMENTS[@]}"
  do
    for bench in "${SEQ_BENCHES[@]}"
    do
      yes | cp -f $bench_root/$bench/instrumented/${EXPERIMENTS[$exp]} $toplvl/results/$exp/raw/$bench
      if [ "$exp" == "Init_Costs-Table6" ] || [ "$exp" == "Mem_Util-Table5" ] ; then
        yes | cp -f $bench_root/$bench/instrumented/res.out $toplvl/results/$exp/raw/$bench"_time"
      fi
    done
    for bench in "${!PAR_BENCHES[@]}"
    do
      yes | cp -f $bench_root/$bench/${PAR_BENCHES[$bench]}/${EXPERIMENTS[$exp]} $toplvl/results/$exp/raw/$bench
      yes | cp -f $bench_root/$bench/${PAR_BENCHES[$bench]}/res.out $toplvl/results/$exp/raw/$bench"_time"
    done
  done
}

function init {
  pwd="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
  bench_root=$pwd/..
  toplvl=$bench_root/../..

  mkdir -p $toplvl/results

  for exp in "${!EXPERIMENTS[@]}"
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
# (export PROF_TYPE="NOPROF" ; run)
collect
