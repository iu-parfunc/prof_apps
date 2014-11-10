
.PHONY: all clean run

all: clean run	

build:
	chmod u+x setup.sh
	./setup.sh 
	cd ../instrumented;\
	make clean;\
	make CFLAGS='-O2'

run: build
	cd ../instrumented;\
  (/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./bzip2 test/input/input.source) 2>&1 ;\

clean:
