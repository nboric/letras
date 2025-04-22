cmake_minimum_required(VERSION 3.31)
project(letras)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(letras main.cpp
        board.h
        board.cpp
        tile.h
        tile.cpp
        player.cpp
        player.h
        square.cpp
        square.h
        game.cpp
        game.h
        bag.cpp
        bag.h
        dict.cpp
        dict.h
)

target_link_libraries(letras PRIVATE SFML::Graphics)