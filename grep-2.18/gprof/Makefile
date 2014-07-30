
include ../Makefile_common

run: build-prof
	$(MAKE) run-common
	(cd ../instrumented/src; gprof grep gmon.out | tee ../../gprof.out)

clean:
