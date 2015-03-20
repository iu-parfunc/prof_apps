.PHONY: all clean run

all: clean run	

build:
	cd ../quickHull;\
	make clean;\
	make 

DATADIR=/u/crest-team/ubiprof_data

run: build
	cd ../quickHull;\
  (/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./hull $(DATADIR)/hull_data.input) 2>&1 ;\

clean:
