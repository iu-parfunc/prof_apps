
bench:
	./scripts/build_bench.sh -s	
	./scripts/build_bench.sh -p

run:
	./scripts/run_bench.sh -s
	./scripts/run_bench.sh -p

clean:
	rm -rf h264ref-9.3/instrumented
	rm -rf bzip-1.0.3/instrumented
	rm -rf perl-5.8.7/instrumented
	rm -rf sjeng/instrumented
	rm -rf hmmer/instrumented
	rm -rf nbody/BarnesHut/*.o nbody/BarnesHut/nbody
	rm -rf hull/quickHull/*.o hull/quickHull/hull
	rm -rf blackscholes/src/*.o blackscholes/src/blackscholes
	rm -rf fluid/src/*.o fluid/src/fluidanimate fluid/src/fluidcmp
