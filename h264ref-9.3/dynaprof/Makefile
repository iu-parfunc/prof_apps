
include ../Makefile_common

build: build-dynaprof

run: 
	$(MAKE) run-common
	cd ../instrumented; cat prof.out; cp prof.out ..

clean:
