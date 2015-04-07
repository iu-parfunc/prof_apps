
.PHONY: default clean run

#all: clean run	
default: 
	echo "Postponing to run"

include ../Makefile_common

build: build-plain
#	cd ..;./setup.sh 
#	cd ../instrumented;\
#	make clean;\
#	make CFLAGS='-O2 -lm'

run: run-common

# This called build! 
# run: 
# 	cd ../instrumented;\
#   (/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./lbm 3000 reference.dat 0 0 data/ref/input/100_100_130_ldc.of) 2>&1 ;\

clean:
