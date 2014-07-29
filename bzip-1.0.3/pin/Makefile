
.PHONY: default clean run

default: 
	echo "Doing nothing during 'compile' phase... procrastinating until run."

build : 
	chmod u+x setup.sh
	./setup.sh
	echo -e "Building h264..."
	cd ../instrumented;\
	make clean;\
	make;\

run: build
	cd ../instrumented;\
	(/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" pin -t ../../resources/fcount.so -- ./bzip2 test/input/input.source) 2>&1;\ 
	cp prof.out ../pin.out 

clean:
