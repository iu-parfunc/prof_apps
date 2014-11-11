
include ../Makefile_common

run: build-prof
	$(MAKE) run-common
	(cd ../instrumented; gprof lbm gmon.out | tee ../gprof.out)

clean:
