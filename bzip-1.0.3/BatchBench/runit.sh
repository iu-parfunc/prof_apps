

RUNID=$1 

set x 
set e

if [ -f data_out.$RUNID ] ; then 
    rm data_out.$RUNID
fi 

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../../build
export PROFILER_TYPE=SAMPLING
export TARGET_OVERHEAD=5


echo "filesize, real, user, sys" > data_out.$RUNID

for i in 1 10 20 30 40 50 60 70 80 90 100 ; do
    (cd ../instrumented; \
     /usr/bin/time -f "$i, %e, %U, %S" -o ../BatchBench/data_out.$RUNID -a \
        ./bzip2 ../BatchBench/large.random $i )
done 

