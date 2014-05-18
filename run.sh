#!/bin/bash

if [ ! -e resources/a ]; then
  cd resources
  chmod u+x filegen
  ./filegen
  cd ..
fi

if [ ! -d "grep-2.18/instrumented" ]; then
  mkdir grep-2.18/instrumented
  mkdir grep-2.18/instrumented/src
fi

if [ ! -d "gzip-1.6/instrumented" ]; then
  mkdir gzip-1.6/instrumented
fi

echo -e "Finished creating directories"

cd gzip-1.6
chmod u+x run_benchmarks.sh
./run_benchmarks.sh
cd ../grep-2.18
chmod u+x run_benchmarks.sh
./run_benchmarks.sh
cd ..
