build: build-noprof

include ../Makefile_common

run: 
	echo "Creating functions.txt" 
	(cd ../src; readelf -s blackscholes |grep FUNC | awk -F '[[:space:]]+' '{print $$3 "," $$9}' > functions.txt)
	echo "Entering run-common" 
	$(MAKE) run-noprof

clean:

