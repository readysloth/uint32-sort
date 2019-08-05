#!/bin/bash
mkdir build
cd build
~/cmake/cmake-3.15.0-Linux-x86_64/bin/cmake -DCMAKE_BUILD_TYPE=Debug ../src/
make 
cp uint32_sort_gui ..
