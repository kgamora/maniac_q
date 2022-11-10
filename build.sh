#!/bin/bash

rm -rf build && mkdir build && cd build && CXX=g++ CC=gcc cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release .. && make -j
