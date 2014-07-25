
.PHONY: all clean run

all: clean run	

build:
	chmod u+x setup.sh
	./setup.sh 
	cd ..; ./instrument.sh
	cd ../instrumented;\
	make clean;\
	make

run: build
	cd ../instrumented;\
  (/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./perlbench -Ilib test/input/diffmail.pl 4 800 10 17 19 300) 2>&1 ;\
	cp prof.out ..
#	(time ./gzip -c ../../resources/a > a.gz);
# echo -e "\nRunning instrumented binary..."
#	./run_benchmarks.sh

clean:
