
.PHONY: all clean run

all: clean run	

build:
	chmod u+x setup.sh
	./setup.sh
	cd ../instrumented;\
	autoreconf;\
	./configure CC=gcc CFLAGS='-pg';\
	make

run: build
	cd ../instrumented/src;\
	(/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./grep -rl test ../../../.. > /dev/null) 2>&1;\
	gprof grep gmon.out > ../../gprof.out

clean:
