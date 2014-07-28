

include ../Makefile_common

run: build-prof
	$(MAKE) run-common
	(cd ../instrumented; gprof gzip gmon.out | tee ../gprof.out)
