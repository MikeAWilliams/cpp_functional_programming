cmake_minimum_required (VERSION 3.0)
project (chapter08)

include_directories(
    ~/vcpkg/installed/x64-linux/include)

 find_package(Immer CONFIG REQUIRED)

add_executable(chapter08 main.cpp helloImmer.cpp undoStack.cpp)
target_link_libraries(chapter08 PRIVATE immer)
set_property(TARGET chapter08 PROPERTY CXX_STANDARD 17)