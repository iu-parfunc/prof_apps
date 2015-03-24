

RUNID=$1 

EXECDIR=../quickHull
EXECUTABLE=./hull


if [ -f data_out.$RUNID ] ; then 
    rm data_out.$RUNID
fi 


export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../../build 


export PROFILER_TYPE=FIXED_BACKOFF 

echo "variant, real, user, sys" > data_out.$RUNID 

if [ $RUNID = ubiprof ] ; then
for i in 1000000 10000000 20000000 30000000 40000000 50000000 60000000 70000000 80000000 90000000 100000000 ; do 
    
    export SAMPLE_SIZE=$i 

    for retry in 1 2 3 4 5; do
    (cd $EXECDIR ; \
	/usr/bin/time -f "backoff_$i, %e, %U, %S" -o ../ManuBench/data_out.$RUNID -a \
	   $EXECUTABLE ../ManuBench/input.data)
    if [ $? = 0 ] ; then break 
    fi
    done
done
else 
  (cd $EXECDIR ; \
	/usr/bin/time -f "unprofiled %e, %U, %S" -o ../ManuBench/data_out.$RUNID -a \
	   $EXECUTABLE ../ManuBench/input.data)
  
fi






