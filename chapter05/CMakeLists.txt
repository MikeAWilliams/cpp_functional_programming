cmake_minimum_required (VERSION 3.0)
project (chapter05)

include_directories(
    /mnt/d/data/programming/cpp/vcpkg/installed/x64-linux/include)

add_executable(chapter05 chapter05_main.cpp copy_assignment_performance.cpp)