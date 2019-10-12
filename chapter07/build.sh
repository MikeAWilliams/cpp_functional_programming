#!/bin/bash
cmake -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=release "-DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake" 
cmake --build .
./chapter07