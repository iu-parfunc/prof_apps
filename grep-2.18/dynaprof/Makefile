
build: build-dynaprof

include ../Makefile_common

run: 
	$(MAKE) run-common
	(cd ../instrumented/src; head -n50 prof.out)
	(cd ../instrumented/src; cp prof.out ../..)

clean:
