



What is this?
-------------

This directory contains application benchmarks that run with DynaProf
and other profiling modes.

Protocol for all benchmarks
---------------------------

 * Each subdirectory, bench/variant, supports:
  - `make clean`: 
  - `make build`: build the benchmark
  - `make run`: run the benchmark (use RUN_ARGS for cmd line args if necessary)
