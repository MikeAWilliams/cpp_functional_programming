cmake_minimum_required (VERSION 3.0)
project (chapter04)

include_directories(
    ~/vcpkg/installed/x64-linux/include)

add_executable(chapter04 chapter04_main.cpp currying_performance.cpp lifting.cpp)