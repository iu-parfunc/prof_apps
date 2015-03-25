

RUNID=$1 

if [ -f data_out.$RUNID ] ; then 
    rm data_out.$RUNID
fi 


export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../../build 


export PROFILER_TYPE=FIXED_BACKOFF 

echo "run, backoff, real, user, sys" > data_out.$RUNID 

if [ $RUNID = ubiprof ] ; then
for i in 1000000 10000000 20000000 30000000 40000000 50000000 60000000 70000000 80000000 90000000 100000000 ; do 
    
    export SAMPLE_SIZE=$i 
    for round in 1 2 3 4 5 6; do 
    for retry in 1 2 3 4 5; do
    (cd ../BarnesHut; \
	/usr/bin/time -f "$round, $i, %e, %U, %S" -o ../ManuBench/data_out.$RUNID -a \
	   ./nbody ../ManuBench/input.data)
    if [ $? = 0 ] ; then break 
    fi
    done
    done
done
else 
    for round in 1 2 3 4 5 6; do
     (cd ../BarnesHut; \
 	/usr/bin/time -f "$round, unprofiled, %e, %U, %S" -o ../ManuBench/data_out.$RUNID -a \
	 ./nbody ../ManuBench/input.data)
     done
  
fi






