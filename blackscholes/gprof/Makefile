
include ../Makefile_common

build: build-prof

run:
	$(MAKE) run-common
	(cd ../src; gprof blackscholes gmon.out  | tee ../gprof.out)

clean:
