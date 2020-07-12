# This is cmake for the authors example. You can get the example from https://gitlab.com/manning-fpcpp-book/code-examples/-/tree/master/chapter-12/bookmark-service
# After build it and run it it expects you to send it json via http, example telnet 127.0.0.1 42042. An example json is "{ "FirstURL":"www.google.com", "Text":"C++ stuff"}"
cmake_minimum_required (VERSION 3.0)
project (bookmark)

file(GLOB SOURCES
    *.cpp
)

add_executable(bookmark ${SOURCES})
set_property(TARGET bookmark PROPERTY CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

find_package(nlohmann_json CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)

target_link_libraries(bookmark PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(bookmark PRIVATE range-v3)