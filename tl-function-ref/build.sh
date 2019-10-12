#!/bin/bash
cmake -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=release "-DCMAKE_TOOLCHAIN_FILE=/home/mwilliams/vcpkg/scripts/buildsystems/vcpkg.cmake" 
cmake --build .
./main