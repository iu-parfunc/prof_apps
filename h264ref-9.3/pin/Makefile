
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
	(/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" pin -filter_no_shared_libs -t ../../resources/fcount.so -- ./h264ref -d test/input/foreman_test_encoder_baseline.cfg) 2>&1 ;\ 
	cp prof.out ../pin.out 

clean:
