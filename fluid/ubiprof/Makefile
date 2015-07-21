build: build-ubiprof

include ../Makefile_common

run: 
	echo "The user running this benchmark is:"
	whoami
	echo "Creating functions.txt" 
	readelf --version
	(cd ../src; readelf -s fluidanimate |grep FUNC | awk -F '[[:space:]]+' '{print $$3 "," $$9}' > functions.txt)
	echo "Entering run-common" 
	$(MAKE) run-common
	echo "Displaying profiler output" 
	(cd ../src; head -n50 prof.out)
	(cd ../src; cp prof.out ..)

clean:

