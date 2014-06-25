
.PHONY: all clean run

all: clean run	

build:
	chmod u+x setup.sh
	./setup.sh
	cd ../instrumented; \
	autoreconf; \
	./configure CC=icc LIBS='libdynaprof.a libzca-toggle.a -lelf' CLFAGS='-O2';\
	make;\
	echo -e "\nInstrumenting gzip...";
	cd ..; ./instrument.sh;\
	echo -e "\nBuilding gzip with instrumentation...";
	cd ../instrumented;\
	make clean;\
	make

run: build
	cd ../instrumented;\
  (/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./gzip -c ../../resources/a > a.gz) 2>&1 ;\
	cp prof.out ..
#	(time ./gzip -c ../../resources/a > a.gz);
# echo -e "\nRunning instrumented binary..."
#	./run_benchmarks.sh

clean:
