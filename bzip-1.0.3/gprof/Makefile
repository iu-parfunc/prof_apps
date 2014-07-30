
include ../Makefile_common

run: build-prof
	$(MAKE) run-common
	(cd ../instrumented; gprof bzip2 gmon.out | tee ../gprof.out)

clean:
