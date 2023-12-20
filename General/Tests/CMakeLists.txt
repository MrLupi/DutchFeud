cmake_minimum_required(VERSION 3.1)

project(general_tests C)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARIES}) 

#add_executable(PlayFieldTests PlayFieldTests.cpp)
#target_link_libraries(PlayFieldTests common ${Boost_LIBRARIES})
#add_test(PlayFieldTests PlayFieldTests)
