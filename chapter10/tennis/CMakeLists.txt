cmake_minimum_required (VERSION 3.0)
project (tennis)

include_directories(
    ~/vcpkg/installed/x64-linux/include)

add_executable(tennis 
   main.cpp
   tennis.cpp
   tennisLogger.cpp
   testTennis.cpp
   testLogger.cpp
   testTennisLogger.cpp)
   
set_property(TARGET tennis PROPERTY CXX_STANDARD 17)