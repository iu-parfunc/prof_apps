
include ../Makefile_common

run: build-prof
	$(MAKE) run-common
	(cd ../BarnesHut; gprof nbody gmon.out  | tee ../gprof.out)

clean:
