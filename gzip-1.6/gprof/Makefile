
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
	(time ./gzip -c ../../resources/a > a.gz) 2> ../gprof_time;\
	gprof gzip gmon.out > ../gprof.out
#	echo -e "\nRunning gzip..."
# ./run_benchmarks.sh
#	echo -e "Done.."

clean:
