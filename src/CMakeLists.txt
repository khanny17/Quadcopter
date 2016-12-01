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
    AttitudeDeterminator
    Controller
    Motors
    Utils
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

cotire(Quadcopter)

# MOAR WARNINGS
include(CheckCXXCompilerFlag)

function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
    endif()
endfunction()

# example usage
enable_cxx_compiler_flag_if_supported("-Wall")
enable_cxx_compiler_flag_if_supported("-Wextra")
enable_cxx_compiler_flag_if_supported("-pedantic")
