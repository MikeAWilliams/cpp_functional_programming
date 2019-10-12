# CMakeLists.txt
cmake_minimum_required (VERSION 3.0)
project (test_optional)

include_directories(
    ~/vcpkg/installed/x64-linux/include)

add_executable(chapter06 main.cpp lazy_sort.cpp simple_sort.cpp)