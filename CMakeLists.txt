cmake_minimum_required(VERSION 3.17)
project(terminal_game)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(terminal_game
        src/fulecoSimpleSemaphore.cpp
        src/fulecoSimpleSemaphore.h
        src/main.cpp)
