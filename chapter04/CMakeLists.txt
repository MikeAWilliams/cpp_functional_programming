cmake_minimum_required (VERSION 2.8.9)
project (chapter04)

include_directories(../../third/Catch2/single_include/)
include_directories(../../third/range-v3/include/)

add_executable(chapter04 chapter04_main.cpp currying_performance.cpp lifting.cpp)