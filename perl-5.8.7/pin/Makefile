
.PHONY: default clean run

default: 
	echo "Doing nothing during 'compile' phase... procrastinating until run."

build:
	chmod u+x setup.sh
	./setup.sh 
	cd ../instrumented;\
  make clean;\
	make

run: build
	cd ../instrumented;\
	(/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" pin -t ../../resources/fcount.so -- ./perlbench -Ilib test/input/diffmail.pl 4 800 10 17 19 300) 2>&1 ;\ 
	cp pin.out ../pin.out 

clean:
