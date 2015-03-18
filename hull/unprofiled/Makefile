.PHONY: all clean run

all: clean run	

build:
	cd ../quickHull;\
	make clean;\
	make 

run: build
	cd ../quickHull;\
  (/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./hull ../Data/data.out) 2>&1 ;\

clean:
