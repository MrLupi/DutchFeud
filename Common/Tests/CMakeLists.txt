cmake_minimum_required(VERSION 3.1)

project(common_tests C)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories(${common_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
link_directories(${common_LIBRARY_DIRS} ${Boost_LIBRARIES}) 

add_executable(PlayFieldTests PlayFieldTests.cpp)
target_link_libraries(PlayFieldTests common ${Boost_LIBRARIES})
add_test(PlayFieldTests PlayFieldTests)

add_executable(PlayFieldSquareTests PlayFieldSquareTests.cpp)
target_link_libraries(PlayFieldSquareTests common ${Boost_LIBRARIES})
add_test(PlayFieldSquareTests PlayFieldSquareTests)

add_executable(PlayFieldLocationTests PlayFieldLocationTests.cpp)
target_link_libraries(PlayFieldLocationTests common ${Boost_LIBRARIES})
add_test(PlayFieldLocationTests PlayFieldLocationTests)

add_executable(TileTests TileTests.cpp)
target_link_libraries(TileTests common ${Boost_LIBRARIES})
add_test(TileTests TileTests)

add_executable(TilesCollectionTests TilesCollectionTests.cpp)
target_link_libraries(TilesCollectionTests common ${Boost_LIBRARIES})
add_test(TilesCollectionTests TilesCollectionTests)