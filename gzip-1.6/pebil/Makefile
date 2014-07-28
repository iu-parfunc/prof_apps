
.PHONY: default clean run

default: 
	echo "Doing nothing during 'compile' phase... procrastinating until run."

build : 
	chmod u+x setup.sh
	./setup.sh
	echo -e "Building gzip..."
	cd ../instrumented;\
	autoreconf;\
	./configure CC=gcc;\
	make;\
	pebil --typ jbb --app gzip --out gzip_jbb

run: build
	cd ../instrumented;\
	(/usr/bin/time -f "SELFTIMED %e\nuser %U\nsys %S\n" ./gzip_jbb -c ../../resources/a > a.gz) 2>&1;\
	cp *.jbbinst ../pebil.out
#	(time ./gzip -c ../../resources/a > a.gz) 2> ../original_time
#	echo -e "\nRunning gzip..."

clean:
