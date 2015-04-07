
.PHONY: default clean run

default: 
	echo "Postponing to run"

include ../Makefile_common

build: build-plain

run: run-common

clean:

# .PHONY: all clean run

# all: clean run	

# build:
# 	cd ..;./setup.sh 
# 	cd ../instrumented;\
# 	make clean;\
# 	make CFLAGS='-O2'

# run: build
# 	cd ../instrumented;\
#   (/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./sjeng test/input/test.txt) 2>&1 ;\

# clean:
