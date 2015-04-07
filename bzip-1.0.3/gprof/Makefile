
include ../Makefile_common

build: build-prof

run: 
	$(MAKE) run-common
	(cd ../instrumented; gprof bzip2 gmon.out | tee ../gprof.out)

clean:
