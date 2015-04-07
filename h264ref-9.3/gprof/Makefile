
include ../Makefile_common

build: build-prof

run: 
	$(MAKE) run-common
	(cd ../instrumented; gprof h264ref gmon.out | tee ../gprof.out)

clean:
