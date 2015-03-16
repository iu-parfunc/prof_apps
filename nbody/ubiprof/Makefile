build: build-ubiprof

include ../Makefile_common

run: 
	(cd ../BarnesHut; readelf -s nbody |grep FUNC | awk -F '[[:space:]]+' '{print $$3 "," $$9}' > functions.txt)
	$(MAKE) run-common
	(cd ../BarnesHut; head -n50 prof.out)
	(cd ../BarnesHut; cp prof.out ..)

clean:
