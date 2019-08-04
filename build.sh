#!/bin/bash
mkdir build
cd build
cmake ../src/
make 
cp uint32_sort_gui ..
