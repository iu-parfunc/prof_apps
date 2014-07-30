
include ../Makefile_common

run: build-dynaprof 
	$(MAKE) run-common
	cd ../instrumented; cat prof.out; cp prof.out ..

clean:
