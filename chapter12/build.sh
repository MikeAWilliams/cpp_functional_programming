#!/bin/bash

# This is builds the authors example. You can get the example from https://gitlab.com/manning-fpcpp-book/code-examples/-/tree/master/chapter-12/bookmark-service
# After build it and run it it expects you to send it json via http, example telnet 127.0.0.1 42042. An example json is "{ "FirstURL":"www.google.com", "Text":"C++ stuff"}"
SCRIPTPATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
CMAKE_DIR=$SCRIPTPATH/build-dir/linux/cmake

mkdir -p $CMAKE_DIR
cd $CMAKE_DIR

# find vcpkg in $PATH
#   if vcpkg is not in $PATH, then the cmake script will download and install vcpkg
VCPKG_ROOT="$( dirname "$( which vcpkg )" )"
echo $VCPKG_ROOT

cmake -G "Unix Makefiles" $SCRIPTPATH \
    -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake \
    && make && ./bookmark

cd $SCRIPTPATH
