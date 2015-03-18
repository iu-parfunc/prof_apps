build: build-ubiprof

include ../Makefile_common

run: 
	echo "Creating functions.txt" 
	(cd ../quickHull; readelf -s hull |grep FUNC | awk -F '[[:space:]]+' '{print $$3 "," $$9}' > functions.txt)
	echo "Entering run-common" 
	$(MAKE) run-common
	echo "Displaying profiler output" 
	(cd ../BarnesHut; head -n50 prof.out)
	(cd ../BarnesHut; cp prof.out ..)

clean:

