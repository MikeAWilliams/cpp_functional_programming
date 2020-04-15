cmake_minimum_required (VERSION 3.0)
project (chapter03)

include_directories(
    ~/vcpkg/installed/x64-linux/include)

add_executable(chapter03 main.cpp reversePolishCalculator.cpp)
set_property(TARGET chapter03 PROPERTY CXX_STANDARD 17)