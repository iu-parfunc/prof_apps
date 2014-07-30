
include ../Makefile_common

build: build-dynaprof

run: 
	$(MAKE) run-common
	cd ../instrumented/src; cat prof.out; cp prof.out ../..

clean:
