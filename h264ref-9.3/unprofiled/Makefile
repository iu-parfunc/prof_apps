
.PHONY: all clean run

all: clean run	

build:
	chmod u+x setup.sh
	./setup.sh 
	cd ../instrumented;\
	make clean;\
	make

run: build
	cd ../instrumented;\
  (/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./h264ref -d test/input/foreman_test_encoder_baseline.cfg) 2>&1 ;\

clean:
