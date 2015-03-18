build: build-ubiprof

include ../Makefile_common

run: 
	echo "Creating functions.txt" 
	(cd ../BarnesHut; readelf -s nbody |grep FUNC | awk -F '[[:space:]]+' '{print $$3 "," $$9}' > functions.txt)
	echo "Entering run-common" 
	$(MAKE) run-common
	echo "Displaying profiler output" 
	(cd ../BarnesHut; head -n50 prof.out)
	(cd ../BarnesHut; cp prof.out ..)

clean:


# [hsbencher]  [stderr] head: cannot open `prof.out' for reading: No such file or directory
#  [hsbencher]  [stderr] make[1]: *** [run] Error 1
#  [hsbencher]  [stdout] make[1]: Entering directory `/tmp/jenkins_slaves/wolverine/workspace/benchmark_dynaprof_new/BENCHROOT/nbody/CABAL/cabal-1.18.0/JENKINS_GHC/7.8.2/PROF/0/VARIANT/ubiprof/label/soic-xmen/benchmarks/nbody/ubiprof'
#  [hsbencher]  [stdout] (cd ../BarnesHut; readelf -s nbody |grep FUNC | awk -F '[[:space:]]+' '{print $3 "," $9}' > functions.txt)
#  [hsbencher]  [stdout] make run-common
#  [hsbencher]  [stdout] make[2]: Entering directory `/tmp/jenkins_slaves/wolverine/workspace/benchmark_dynaprof_new/BENCHROOT/nbody/CABAL/cabal-1.18.0
