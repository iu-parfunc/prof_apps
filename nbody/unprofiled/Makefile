.PHONY: all clean run

all: clean run	

build:
	cd ../BarnesHut;\
	make clean;\
	make 

run: build
	cd ../BarnesHut;\
  (/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./nbody ../Data/data.out) 2>&1 ;\

clean:
