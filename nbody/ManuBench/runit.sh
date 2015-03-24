

RUNID=$1 

if [ -f data_out.$RUNID ] ; then 
    rm data_out.$RUNID
fi 


export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../build 


export PROFILER_TYPE=FIXED_BACKOFF 

echo "real, user, sys" > data_out.$RUNID 

for i in 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000 ; do 
    
    export SAMPLE_SIZE=$i 

    (cd ../BarnesHut; \
	/usr/bin/time -f "%e, %U, %S" -o ../ManuBench/data_out.$RUNID -a \
	   ./nbody ../ManuBench/input.data)
    
done







