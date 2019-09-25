cmake_minimum_required (VERSION 3.0)
project (hello)

include_directories(
    /mnt/d/data/programming/cpp/vcpkg/installed/x64-linux/include)

add_executable(hello hello.cpp)