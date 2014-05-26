
.PHONY: all clean run

all: clean run	

build:
	chmod u+x setup.sh
	./setup.sh
	cd ../instrumented; \
	autoreconf; \
	./configure CC=icc LIBS='libdynaprof.a libzca-toggle.a -lelf' CFLAGS='-O0';\
	make;\
	echo -e "\nInstrumenting gzip...";
	cd ..; ./instrument.sh;\
	echo -e "\nBuilding gzip with instrumentation...";
	cd ../instrumented;\
	make clean;\
	make

run: build
	cd ../instrumented;\
	(time ./gzip -c ../../resources/a > a.gz) 2> ../dynaprof_time;\
	cp prof.out ..
# echo -e "\nRunning instrumented binary..."
#	./run_benchmarks.sh

clean:
