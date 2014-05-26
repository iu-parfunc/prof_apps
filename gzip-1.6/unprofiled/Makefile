
.PHONY: all clean run

all: clean run	

build : 
	chmod u+x setup.sh
	./setup.sh
	echo -e "Building gzip..."
	cd ../instrumented;\
	autoreconf;\
	./configure CC=gcc;\
	make;\

run: build
	cd ../instrumented;\
	(time ./gzip -c ../../resources/a > a.gz) 2> ../original_time
#	echo -e "\nRunning gzip..."

clean:
