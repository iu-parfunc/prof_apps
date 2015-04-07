
include ../Makefile_common

build: build-prof

run: 
	$(MAKE) run-common
	(cd ../BarnesHut; gprof nbody gmon.out  | tee ../gprof.out)

clean:
