#!/bin/bash
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
make -f Makefile
./chapter01