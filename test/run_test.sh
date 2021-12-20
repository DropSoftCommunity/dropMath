#!/bin/sh

cd ./build/
cmake ..
make
./drop_math_test
