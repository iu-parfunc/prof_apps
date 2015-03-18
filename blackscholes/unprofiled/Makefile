.PHONY: all clean run

all: clean run	

build:
	cd ../src;\
	make 

run: build
	cd ../src;\
  (/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./blackscholes 8 data.out \dev\null) 2>&1 ;\

clean:
