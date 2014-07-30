
build: build-dynaprof 

include ../Makefile_common

run: 
	$(MAKE) run-common
	cd ../instrumented; cat prof.out; cp prof.out ..

clean:
