project(Motors)

#file(GLOB MOTORS_SOURCES *.cpp *.h)

set( MOTORS_SOURCES
    Motors.cpp
    Motors.h
    Servo.cpp
    Servo.h)


add_library(Motors ${MOTORS_SOURCES})
