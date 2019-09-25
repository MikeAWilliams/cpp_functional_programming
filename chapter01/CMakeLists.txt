cmake_minimum_required (VERSION 2.8.9)
project (chapter01)

include_directories(../../third/Catch2/single_include/)
include_directories(../../third/range-v3/include/)

add_executable(chapter01 chapter01.cpp)