
.PHONY: all clean run

all: clean run

build:
	chmod u+x setup.sh
	./setup.sh
	cd ..; ./instrument.sh
	cd ../instrumented/bzip2-1.0.6;\
  make clean;\
	make
	cp ../instrumented/bzip2-1.0.6/libbz2.a ../instrumented
	cp ../instrumented/bzip2-1.0.6/bzlib.h ../instrumented
	cd ../instrumented;\
	make clean;\
	make pbzip2-static

run: build
	cd ../instrumented;\
	(time ./pbzip2 -c ../../resources/a > a.bz2) 2> ../dynaprof_time;\
	cp prof.out ..

