cmake_minimum_required (VERSION 3.0)
project (chapter07)

include_directories(
    ~/vcpkg/installed/x64-linux/include)

add_executable(chapter07 main.cpp rtest.cpp test_mrange.cpp random_examples.cpp)
set_property(TARGET chapter07 PROPERTY CXX_STANDARD 17)