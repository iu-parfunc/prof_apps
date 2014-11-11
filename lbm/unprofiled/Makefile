
.PHONY: all clean run

all: clean run	

build:
	cd ..;./setup.sh 
	cd ../instrumented;\
	make clean;\
	make CFLAGS='-O2'

run: build
	cd ../instrumented;\
  (/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./lbm 3000 reference.dat 0 0 data/ref/input/100_100_130_ldc.of) 2>&1 ;\

clean:
