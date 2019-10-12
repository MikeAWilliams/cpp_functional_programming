cmake_minimum_required (VERSION 3.0)
project (main)

include_directories(
    ~/vcpkg/installed/x64-linux/include)

find_package(tl-function-ref CONFIG REQUIRED)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE tl::function-ref)