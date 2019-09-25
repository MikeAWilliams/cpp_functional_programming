cmake_minimum_required (VERSION 2.8.9)
project (hello)

include_directories(../../third/Catch2/single_include/)
include_directories(../../third/range-v3/include/)

add_executable(hello hello.cpp)