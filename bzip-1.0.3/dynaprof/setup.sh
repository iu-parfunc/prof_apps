#!/bin/bash

set -e 

if [ -d "../instrumented" ]; then
  rm -rf ../instrumented
fi

cp -R ../original ../instrumented
cp make ../instrumented/Makefile

chmod u+x ../../install.sh
cd ../../ ;\
./install.sh bzip2

echo -e "\n Installed dynaprof..."




