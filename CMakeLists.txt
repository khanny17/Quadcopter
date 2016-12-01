cmake_minimum_required (VERSION 3.2)

project (Quadcopter)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

include(cotire)

add_subdirectory(src)
