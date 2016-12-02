cmake_minimum_required (VERSION 3.2)

project (Quadcopter)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

set (CMAKE_CXX_STANDARD 11)

include(cotire)

add_subdirectory(src)
