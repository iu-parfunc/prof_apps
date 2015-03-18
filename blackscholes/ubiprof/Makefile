build: build-ubiprof

include ../Makefile_common

run: 
	echo "Creating functions.txt" 
	(cd ../src; readelf -s nbody |grep FUNC | awk -F '[[:space:]]+' '{print $$3 "," $$9}' > functions.txt)
	echo "Entering run-common" 
	$(MAKE) run-common
	echo "Displaying profiler output" 
	(cd ../src; head -n50 prof.out)
	(cd ../src; cp prof.out ..)

clean:

