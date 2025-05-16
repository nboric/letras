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
        src/play_rules/play_rule.h
        src/play_rules/contiguous.cpp
        src/play_rules/contiguous.h
        src/play_rules/dict_check.cpp
        src/play_rules/dict_check.h
        src/score.cpp
        src/score.h
        src/play_rules/first_move.cpp
        src/play_rules/first_move.h
        src/basic_types.h
        src/play_rules/play.cpp
        src/play_rules/play.h
        src/play_rules/connected.cpp
        src/play_rules/connected.h
        src/play_rules/play_builder.cpp
        src/play_rules/play_builder.h
        src/play_rules/calc_score.cpp
        src/play_rules/calc_score.h
)

target_link_libraries(letras PRIVATE SFML::Graphics)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(letras PUBLIC FONT_PATH="/System/Library/Fonts/SFCompact.ttf")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(letras PUBLIC FONT_PATH="c:/windows/Fonts/verdana.ttf")
endif()

FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(letras_tests
        src/dict.cpp
        src/dict.h
        src/square.cpp
        src/square.h
        src/tile.h
        src/tile.cpp
        src/board.h
        src/board.cpp
        src/play_rules/play.cpp
        src/play_rules/play.h
        src/play_rules/contiguous.cpp
        src/play_rules/contiguous.h
        src/play_rules/first_move.cpp
        src/play_rules/first_move.h
        src/play_rules/connected.cpp
        src/play_rules/connected.h
        test/dict_tests.cpp
        test/play_rules_tests.cpp
        test/mocks.h
)

target_link_libraries(letras_tests PRIVATE SFML::Graphics gmock gtest gtest_main)