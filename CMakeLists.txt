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

add_executable(letras src/main.cpp
        src/board.h
        src/board.cpp
        src/tile.h
        src/tile.cpp
        src/player.cpp
        src/player.h
        src/square.cpp
        src/square.h
        src/game.cpp
        src/game.h
        src/bag.cpp
        src/bag.h
        src/dict.cpp
        src/dict.h
        src/Button.cpp
        src/Button.h
        src/restrictions/restriction.h
        src/restrictions/contiguous.cpp
        src/restrictions/contiguous.h
        src/restrictions/dict_check.cpp
        src/restrictions/dict_check.h
)

target_link_libraries(letras PRIVATE SFML::Graphics)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(letras PUBLIC FONT_PATH="/System/Library/Fonts/SFCompact.ttf")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(letras PUBLIC FONT_PATH="c:/windows/Fonts/verdana.ttf")
endif()