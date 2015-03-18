
include ../Makefile_common

run: build-prof
	$(MAKE) run-common
	(cd ../src; gprof blackscholes gmon.out  | tee ../gprof.out)

clean:
