

include ../Makefile_common

# Temp, set this globally:
# DYNAPROF_ROOT=`pwd`/../../../../

# ./setup.sh direct_10
# ./configure CC=icc LIBS='libdynaprof.a libzca-toggle.a -lelf' CLFAGS='-O2';\
# make;\

run: 
	rm -rf ../instrumented
	cp -R ../original ../instrumented
	(cd ../../; ./install.sh raxml)
	(cd ..; ./instrument.sh)
	$(MAKE) MORELIBS="-lelf $(DYNAPROF_ROOT)/libdynaprof.a $(DYNAPROF_ROOT)/libzca-toggle.a " build-plain
	$(MAKE) run-common
