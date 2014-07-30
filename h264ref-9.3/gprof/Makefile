
include ../Makefile_common

run: build-prof
	$(MAKE) run-common
	(cd ../instrumented; gprof h264ref gmon.out | tee ../gprof.out)

clean:
