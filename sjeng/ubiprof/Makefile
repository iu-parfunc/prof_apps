
build: build-ubiprof

include ../Makefile_common

run: 
	(cd ../instrumented; readelf -s sjeng |grep FUNC | awk -F '[[:space:]]+' '{print $$3 "," $$9}' > functions.txt)
	$(MAKE) run-common
	# (cd ../instrumented; head -n50 prof.out)
	(cd ../instrumented; cp prof.out ..)

clean:
