
include ../Makefile_common

run: build-prof
	$(MAKE) run-common
	(cd ../instrumented; gprof perlbench gmon.out | tee ../gprof.out)

clean:
