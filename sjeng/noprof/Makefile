
build: build-noprof

include ../Makefile_common

run: 
	(cd ../instrumented; readelf -s sjeng |grep FUNC | awk -F '[[:space:]]+' '{print $$3 "," $$9}' > functions.txt)
	$(MAKE) run-noprof

clean:

