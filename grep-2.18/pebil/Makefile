
.PHONY: all clean run

all: clean run	

build:
	chmod u+x setup.sh
	./setup.sh
	cd ../instrumented;\
	autoreconf;\
	./configure CC=gcc;\
	make;\
	cd src;\
	pebil --typ jbb --app grep --out grep_jbb

run: build
	cd ../instrumented/src;\
	(/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./grep_jbb -rl test ../../../.. > /dev/null) 2>&1;\
	cp *.jbbinst ../pebil.out

clean:
