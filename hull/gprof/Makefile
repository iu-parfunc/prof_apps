
include ../Makefile_common

run: build-prof
	$(MAKE) run-common
	(cd ../quickHull; gprof hull gmon.out  | tee ../gprof.out)

clean:
