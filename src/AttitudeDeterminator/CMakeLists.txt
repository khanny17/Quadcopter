project(AttitudeDeterminator)

include_directories({PROJECT_SOURCE_DIR}/)

#file(GLOB ATTITUDE_DETERMINATOR_SOURCES *.cpp *.h)
set(ATTITUDE_DETERMINATOR_SOURCES
    Accelerometer.cpp
    Accelerometer.h
    AttitudeDeterminator.cpp
    AttitudeDeterminator.h
    ComplimentaryFilter.cpp
    ComplimentaryFilter.h
    Gyroscope.cpp
    Gyroscope.h
    IMU.cpp
    IMU.h
    IMUSensor.cpp
    IMUSensor.h
    KalmanFilter.cpp
    KalmanFilter.h
    Filter.h)

find_package(Boost REQUIRED)
include_directories (SYSTEM ${Boost_INCLUDE_DIRS})

add_library(AttitudeDeterminator ${ATTITUDE_DETERMINATOR_SOURCES})
