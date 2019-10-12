cmake_minimum_required (VERSION 3.0)
project (chapter05)

include_directories(
    ~/vcpkg/installed/x64-linux/include)

add_executable(chapter05 chapter05_main.cpp copy_assignment_performance.cpp)