
.PHONY: all clean run

all: clean run	

build : 
	chmod u+x setup.sh
	./setup.sh
	echo -e "Building gzip..."
	cd ../instrumented;\
	autoreconf;\
	./configure CC=icc CFLAGS='-O2';\
	make;\

run: build
	cd ../instrumented;\
	(/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./gzip -c ../../resources/a > a.gz) 2>&1 
#	(time ./gzip -c ../../resources/a > a.gz) 2> ../original_time
#	echo -e "\nRunning gzip..."

clean:
