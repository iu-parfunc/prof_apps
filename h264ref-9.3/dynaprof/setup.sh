#!/bin/bash

if [ -d "../instrumented" ]; then
  rm -rf ../instrumented
fi

cp -R ../original ../instrumented
chmod u+x ../../install.sh
cd ../../ ;\
./install.sh h264 

echo -e "\nInstalled dynaprof..."



