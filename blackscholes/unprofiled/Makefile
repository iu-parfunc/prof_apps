.PHONY: all clean run

all: clean run	

build:
	cd ../src;\
	make CFLAGS='-O2'

DATADIR=/u/crest-team/ubiprof_data

run: build
	cd ../src;\
  (/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./blackscholes 8 $(DATADIR)/blackscholes_data.input \dev\null) 2>&1 ;\

clean:
