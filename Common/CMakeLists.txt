cmake_minimum_required(VERSION 3.1)

project(common CXX)

file(GLOB SOURCES 
    Data/Game.cpp
    Data/GameStore.cpp
    Data/Move.cpp
    Data/MovePart.cpp
    Data/Player.cpp
    Data/PlayerStore.cpp
    Data/PlayField.cpp
    Data/PlayFieldLocation.cpp
    Data/PlayFieldSquare.cpp
    Data/Session.cpp
    Data/SessionStore.cpp
    Data/Tile.cpp
    Data/TilesCollection.cpp
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