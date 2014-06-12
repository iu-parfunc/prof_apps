
.PHONY: all clean run

all: clean run	

build :
	chmod u+x setup.sh
	./setup.sh
	cd ../instrumented;\
	echo -e "Building gzip with gprof enabled...";\
	autoreconf;\
	./configure CC=gcc CFLAGS='-pg';\
	make

run: build
	cd ../instrumented;\
	(/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./gzip -c ../../resources/a > a.gz) 2>&1 ;\
	gprof gzip gmon.out > ../gprof.out
#	(time ./gzip -c ../../resources/a > a.gz) 2> ../gprof_time;
#	echo -e "\nRunning gzip..."
# ./run_benchmarks.sh
#	echo -e "Done.."

clean:
