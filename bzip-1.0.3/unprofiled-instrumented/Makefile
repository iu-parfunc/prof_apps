
.PHONY: default clean run

# all: clean run	
default: 
	echo "Postponing until run" 

build:
	chmod u+x setup.sh
	./setup.sh 
	echo -e "\nInstrumenting h264...";
	cd ..; ./instrument.sh;\
	echo -e "\nBuilding h264 with instrumentation...";
	cd ../instrumented;\
	make clean;\
	make

run: build
	cd ../instrumented;\
  (/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./bzip2 test/input/input.source) 2>&1 ;\

clean:
