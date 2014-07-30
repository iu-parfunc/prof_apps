
build: build-dynaprof

include ../Makefile_common

run: 
	$(MAKE) run-common
	(cd ../instrumented; head -n40 prof.out)
        (cd ../instrumented; cp prof.out ..)

clean:
