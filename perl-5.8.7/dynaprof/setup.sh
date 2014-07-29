#!/bin/bash

set -e 

cp -R ../original ../instrumented
cp make ../instrumented/Makefile

chmod u+x ../../install.sh
cd ../../ ;\
./install.sh perl

