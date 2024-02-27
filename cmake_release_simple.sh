#!/bin/bash

# Check if the 'build' directory exists
if [ -d "build" ]; then
  echo "Deleting contents of existing build directory"
  rm -rf build/*
else
  echo "Creating new build directory"
  mkdir build
fi

# Run other commands one by one
cd build
# cmake ..
cmake -DCMAKE_BUILD_TYPE=Release ..
make
