project(Controller)

#file(GLOB CONTROLLER_SOURCES *.cpp *.h)
set(CONTROLLER_SOURCES
    Controller.cpp
    Controller.h
    PID.cpp
    PID.h)

add_library(Controller ${CONTROLLER_SOURCES})
