
include ../Makefile_common

build: build-prof

run: 
	$(MAKE) run-common
	(cd ../quickHull; gprof hull gmon.out  | tee ../gprof.out)

clean:
