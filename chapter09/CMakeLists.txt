cmake_minimum_required (VERSION 3.0)
project (chapter09)

include_directories(
    ~/vcpkg/installed/x64-linux/include)

add_executable(chapter09 main.cpp tennis.cpp)
set_property(TARGET chapter09 PROPERTY CXX_STANDARD 17)