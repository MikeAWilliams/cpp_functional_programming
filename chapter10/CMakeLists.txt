cmake_minimum_required (VERSION 3.0)
project (chapter10)

include_directories(
    ~/vcpkg/installed/x64-linux/include)

add_executable(chapter10 
   main.cpp
   testOptional.cpp
   testFunctions.cpp
   testTestFunctions.cpp
   testExpected.cpp
   testExpectedFunctional.cpp)
set_property(TARGET chapter10 PROPERTY CXX_STANDARD 17)