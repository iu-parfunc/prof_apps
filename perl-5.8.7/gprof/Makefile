
include ../Makefile_common

build: build-prof

run: 
	$(MAKE) run-common
	(cd ../instrumented; gprof perlbench gmon.out | tee ../gprof.out)

clean:
