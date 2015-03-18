
include ../Makefile_common

run: build-prof
	$(MAKE) run-common
	(cd ../src; gprof fluidanimate gmon.out  | tee ../gprof.out)

clean:
