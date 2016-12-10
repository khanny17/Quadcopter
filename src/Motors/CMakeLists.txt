project(Motors)

#file(GLOB MOTORS_SOURCES *.cpp *.h)

set( MOTORS_SOURCES
    Motors.cpp
    Motors.h
    Servo.cpp
    Servo.h)

find_package(Boost REQUIRED)
include_directories (SYSTEM ${Boost_INCLUDE_DIRS})

add_library(Motors ${MOTORS_SOURCES})

target_link_libraries(Motors
    ${Boost_LIBRARIES} 
    )
