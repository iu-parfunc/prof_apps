
.PHONY: all clean run

all: clean run	

build:
	chmod u+x setup.sh
	./setup.sh direct_10
	echo -e "\nInstrumenting gzip...";
	cd ..; ./instrument.sh;\
	echo -e "\nBuilding gzip with instrumentation...";
	cd ../instrumented;\
	make clean;\
	make

run: build
	cd ../instrumented;\
  (/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./h264ref -d test/input/foreman_test_encoder_baseline.cfg) 2>&1 ;\
	cp prof.out ..
#	(time ./gzip -c ../../resources/a > a.gz);
# echo -e "\nRunning instrumented binary..."
#	./run_benchmarks.sh

clean:
