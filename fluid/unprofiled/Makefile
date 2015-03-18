.PHONY: all clean run

all: clean run	

build:
	cd ../src;\
	make clean;\
	make 

run: build
	cd ../src;\
  (/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./fluidanimate 8 50 in_500K.fluid) 2>&1 ;\

clean:
