#!/usr/bin/env bash

mkdir build
cd build
cmake ..
make
./bin/runner
cd ..
