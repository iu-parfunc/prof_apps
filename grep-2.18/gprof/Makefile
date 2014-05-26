
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
	(time ./grep -rl test ../../../.. > /dev/null) 2> ../../gprof_time;\
	gprof grep gmon.out > ../../gprof.out

clean:
