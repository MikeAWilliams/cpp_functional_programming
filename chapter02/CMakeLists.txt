cmake_minimum_required (VERSION 2.8.9)
project (chapter02)

include_directories(../../third/Catch2/single_include/)
include_directories(../../third/range-v3/include/)

add_executable(chapter02 chapter02.cpp chapter02_07.cpp)