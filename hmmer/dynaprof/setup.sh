#!/bin/bash

if [ -d "../instrumented" ]; then
  rm -rf ../instrumented
fi

cp -R ../original ../instrumented
cp make ../instrumented/Makefile 

chmod u+x ../../install.sh
cd ../../ ;\
./install.sh hmmer

echo -e "\nInstalled dynaprof..."



