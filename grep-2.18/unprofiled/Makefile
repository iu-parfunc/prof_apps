
.PHONY: all clean run

all: clean run	

build:
	chmod u+x setup.sh
	./setup.sh
	cd ../instrumented;\
	autoreconf;\
	./configure CC=gcc;\
	make

run: build
	cd ../instrumented/src;\
	(time ./grep -rl test ../../../.. > /dev/null) 2> ../../original_time

clean:
