project(Controller)

#file(GLOB CONTROLLER_SOURCES *.cpp *.h)
set(CONTROLLER_SOURCES
    Controller.cpp
    Controller.h
    PID.cpp
    PID.h)

find_package(Boost REQUIRED)
include_directories (SYSTEM ${Boost_INCLUDE_DIRS})

add_library(Controller ${CONTROLLER_SOURCES})
