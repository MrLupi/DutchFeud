cmake_minimum_required(VERSION 3.1)

project(server CXX)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")

file(GLOB SOURCES main.cpp FeudServer.cpp)

#add_definitions(${_DEFINITIONS})

include_directories(${common_INCLUDE_DIRS} )

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} common webserver uuid pthread )