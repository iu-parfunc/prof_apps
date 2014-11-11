
build: build-ubiprof

include ../Makefile_common

run: 
	$(MAKE) run-common
	(cd ../instrumented; head -n50 prof.out)
	(cd ../instrumented; cp prof.out ..)

clean:
