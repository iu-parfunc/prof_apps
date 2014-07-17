
DYN_OVERHEAD := "0.05"
DYN_STRATEGY := "BOP_SIMPLE"
DYN_SAMPLE_SIZE := "10000"
						
.PHONY: all clean run

all: clean run	

build:
	chmod u+x ../setup.sh
	cd ..;./setup.sh 
	echo -e "\nInstrumenting h264...";
	cd ../..; ./instrument.sh;\
	echo -e "\nBuilding h264 with instrumentation...";
	cd ../../instrumented;\
	make clean;\
	make

run: build
	cd ../../instrumented;\
  (/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./h264ref -d test/input/foreman_test_encoder_baseline.cfg) 2>&1 ;\
	cp prof.out ..

clean:
