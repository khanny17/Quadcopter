project(Utils C CXX)

#file(GLOB UTILS_SOURCES *.h)
set(UTILS_SOURCES
    UtilityFunctions.h)

include_directories(${PROJECT_SOURCE_DIR}/)

add_library(Utils ${UTILS_SOURCES})
