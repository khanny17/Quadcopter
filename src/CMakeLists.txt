cmake_minimum_required (VERSION 3.5)

project (Quadcopter)

add_subdirectory(AttitudeDeterminator)
add_subdirectory(Controller)
add_subdirectory(Motors)
#add_subdirectory(Utils)

#include Boost
SET(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS
    log
    thread
    date_time
    filesystem
    system
    )

include_directories( 
    ./AttitudeDeterminator
    ./Controller
    ./Motors
    ./Utils
    )
include_directories( SYSTEM
    ${Boost_INCLUDE_DIRS} 
    )

# add the executable
add_executable(Quadcopter "main/main.cpp")

#specify c++11? not sure if thats what this does
target_compile_features(Quadcopter PRIVATE cxx_range_for)

target_link_libraries(Quadcopter
    ${Boost_LIBRARIES} 
    AttitudeDeterminator
    Controller
    Motors
    #Utils
    )


