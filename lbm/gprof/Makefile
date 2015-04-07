
include ../Makefile_common

build: build-prof

run: 
	$(MAKE) run-common
	(cd ../instrumented; gprof lbm gmon.out | tee ../gprof.out)

clean:
