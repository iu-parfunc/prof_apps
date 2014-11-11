
include ../Makefile_common

run: build-prof
	$(MAKE) run-common
	(cd ../instrumented; gprof sjeng gmon.out | tee ../gprof.out)

clean:
