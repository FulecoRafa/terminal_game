cmake_minimum_required(VERSION 3.17)
project(terminal_game)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(terminal_game
        src/character.cpp
        src/character.h
        src/fulecoSimpleSemaphore.cpp
        src/fulecoSimpleSemaphore.h
        src/item.cpp
        src/item.h
        src/main.cpp
        src/map.cpp
        src/map.h
        src/output.cpp
        src/output.h
        src/position.cpp
        src/position.h)
