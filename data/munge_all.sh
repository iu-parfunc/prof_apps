#!/bin/bash

benchs="bzip2 grep gzip h264"
set -xe
topd=`pwd`
OUT=../output

for bench in $benchs; do
    cd $topd/$bench
    mkdir -p $OUT
    ../munge.py    -o $OUT/"$bench"_non_compensated.txt
    ../munge.py -c -o $OUT/"$bench"_compensated.txt
done
