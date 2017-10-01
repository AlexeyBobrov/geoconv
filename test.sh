#!/bin/bash

echo "Build..."
mkdir -p build && cd build
cmake .. 
make -j4
echo "Running test..."
../bin/geoconv_test
