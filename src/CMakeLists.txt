add_subdirectory(AttitudeDeterminator)
add_subdirectory(Controller)
add_subdirectory(Motors)
#add_subdirectory(Utils)

#Find Threads (i.e. pthread compatibility stuff)
find_package(Threads)

#include Boost
SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREADED ON)
find_package(Boost REQUIRED COMPONENTS
    program_options
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

target_link_libraries(Quadcopter
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES} 
    AttitudeDeterminator
    Controller
    Motors
    #Utils
    rt
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
