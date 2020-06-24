cmake_minimum_required (VERSION 3.0)
project (tennis)

include_directories(
    ~/vcpkg/installed/x64-linux/include)

add_executable(tennis 
   main.cpp
   tennis.cpp
   testTennis.cpp
   testLogger.cpp)
   
set_property(TARGET tennis PROPERTY CXX_STANDARD 17)