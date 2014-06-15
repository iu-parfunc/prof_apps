
.PHONY: all clean run

all: clean run	

build:
	chmod u+x setup.sh
	./setup.sh
	cd ../instrumented;\
	autoreconf;\
	./configure CC=icc LIBS='libdynaprof.a libzca-toggle.a -lelf -lpthread' CFLAGS='-O0';\
	make
	cd ..;\
	./instrument.sh
	cd ../instrumented;\
	make clean;\
	make
	
run: build
	cd ../instrumented/src;\
	(/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./grep -rl test ../../../.. > /dev/null) 2>&1;\
	cp prof.out ../..

clean:
