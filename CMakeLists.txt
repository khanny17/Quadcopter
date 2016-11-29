cmake_minimum_required (VERSION 3.5)

project (Quadcopter)

file(GLOB SOURCES "src/**/*.*")

#include Boost
find_package(Boost)
include_directories( ${Boost_INCLUDE_DIRS} )

# add the executable
add_executable(Quadcopter ${SOURCES})

