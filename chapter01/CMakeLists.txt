cmake_minimum_required (VERSION 3.0)
project (chapter01)

include_directories(
    ~/vcpkg/installed/x64-linux/include)

add_executable(chapter01 chapter01.cpp)