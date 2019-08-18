cmake_minimum_required (VERSION 2.8.9)
project (hello)

find_package(Catch2 REQUIRED)

add_executable(hello hello.cpp)
target_link_libraries(hello PRIVATE Catch2::Catch2)