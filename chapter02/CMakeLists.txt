cmake_minimum_required (VERSION 3.0)
project (chapter02)

include_directories(
    /mnt/d/data/programming/cpp/vcpkg/installed/x64-linux/include)

add_executable(chapter02 chapter02.cpp chapter02_07.cpp chapter02_11.cpp chapter02_14.cpp recursive_factorial.cpp)