cmake_minimum_required(VERSION 3.0.0)
project(DutchFeud VERSION 0.1.0)

configure_file ("Headers/config.h.in" "${PROJECT_BINARY_DIR}/Config.h" )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/Cmake/Modules)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror " ) # -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_STANDARD 20)

include(CTest)

include_directories(${PROJECT_BINARY_DIR} .)

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_COLOR_MAKEFILE ON)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

enable_testing()

add_subdirectory(General)
add_subdirectory(Common)
add_subdirectory(WebServer)
add_subdirectory(Server)
