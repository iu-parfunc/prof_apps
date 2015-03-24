

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
for i in 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000 ; do 
    
    export SAMPLE_SIZE=$i 

    (cd $EXECDIR ; \
	/usr/bin/time -f "backoff_$i, %e, %U, %S" -o ../ManuBench/data_out.$RUNID -a \
	   $EXECUTABLE ../ManuBench/input.data)
    
done
else 
  (cd $EXECDIR ; \
	/usr/bin/time -f "unprofiled %e, %U, %S" -o ../ManuBench/data_out.$RUNID -a \
	   $EXECUTABLE ../ManuBench/input.data)
  
fi






