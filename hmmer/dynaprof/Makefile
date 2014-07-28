
.PHONY: all clean run

all: clean run	

build:
	chmod u+x setup.sh
	./setup.sh 
	echo -e "\nInstrumenting hmmer...";
	cd ..; ./instrument.sh;\
	echo -e "\nBuilding hmmer with instrumentation...";
	cd ../instrumented;\
	make clean;\
	make

run: build
	cd ../instrumented;\
  (/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./hmmer ref/input/nph3.hmm ref/input/swiss41) 2>&1 ;\
	cp prof.out ..

clean:
