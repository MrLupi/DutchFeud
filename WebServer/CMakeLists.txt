cmake_minimum_required(VERSION 3.1)

project(webserver CXX)

file(GLOB SOURCES 
    Socket.cpp
    Rest.cpp
)

include_directories(../../)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

# Required on Unix OS family to be able to be linked into shared libraries.
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_link_libraries(${PROJECT_NAME} m)

# Expose B's public includes (including Boost transitively) to other
# subprojects through cache variable.
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

add_subdirectory(Tests)