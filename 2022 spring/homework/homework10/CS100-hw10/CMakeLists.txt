cmake_minimum_required(VERSION 3.5)

project(cs100hw10)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Debug)

#include CTest so we can run unit tests with CMake
include(CTest)

#add directory with include files of this project
include_directories( "${PROJECT_SOURCE_DIR}/include" )

add_subdirectory( src )
add_subdirectory( test )