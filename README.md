



What is this?
-------------

This directory contains application benchmarks that run with DynaProf
and other profiling modes.

Protocol for all benchmarks
---------------------------

 * Each subdirectory, bench/variant, supports:
  - `make clean`: 
  - `make`: build the benchmark
  - `make run`: run the benchmark (use RUN_ARGS for cmd line args if necessary)

 * Variants of one benchmark cannot be built concurrently, they munge
   shared files in each per-benchmark directory.



OLD Running Benchmarks Instructions
===================================

Prequisites
-----------

### PDT

 1. Patch PDT
 2. ./configure -ICPC -prefix=${PDT_INSTALL_LOCATION}
 3. make 
 4. make install

### TAU

 1. ./configure -c++=icpc -pdt_c++=icpc -prefix$={TAU_INSTALL_LOCATION} -pdt=${PDT_INSTALL_LOCATION}
 2. make install

gzip (gzip-1.6)
---------------

1. make ${BUILD_HOME}/zcatoggle/src. This will install the dynaprof libraries and headers to the benchmark application builds.
2. cd ${BUILD_HOME}/benchmarks/gzip-1.6/instrumented
3. If this is the first time the project is being built do 'autoreconf' to regenerate 'configure' file.
4. Do the configure with optional prefix. 
     ./configure CC=icc LIBS='libdynaprof.a libzca-toggle.a -lelf' CFLAGS='-g -O0' --prefix=${GZIP_INSTALL_LOCATION}
5. make (This step is required otherwise there will be errors in the next step)
6. cd ..; ./instrument.sh
7. cd instrumented; make (Now with instrumented files)
8. make install

grep (grep-2.6.1)
-----------------

1. make ${BUILD_HOME}/zcatoggle/src. This will install the dynaprof libraries and headers to the benchmark application builds.
2. cd ${BUILD_HOME}/benchmarks/grep-2.6.1/instrumented
3. Do the configure with optional prefix. 
     ./configure CC=icc LIBS='libdynaprof.a libzca-toggle.a -lelf -lpthread' CFLAGS='-g -O0' --prefix=${GREP_INSTALL_LOCATION}
4. make (This step is required otherwise there will be errors in the next step)
5. cd ..; ./instrument.sh
6. cd instrumented; make (Now with instrumented files)
7. make install


