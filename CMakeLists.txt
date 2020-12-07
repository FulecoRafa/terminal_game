cmake_minimum_required(VERSION 3.6)
project(terminal_game)

set(CMAKE_CXX_STANDARD 11)
set(CURSES_INCLUDE_DIR /usr/local/opt/ncurses/lib)
#set(CMAKE_CXX_FLAGS "-lncurses")

include_directories(io/src)
include_directories(semaphore/src)
include_directories(src)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(terminal_game
        io/src/input.cpp
        io/src/input.h
        io/src/io.h
        io/src/output.cpp
        io/src/output.h
        semaphore/src/fulecoSimpleSemaphore.cpp
        semaphore/src/fulecoSimpleSemaphore.h
        src/character.cpp
        src/character.h
        src/item.cpp
        src/item.h
        src/map.cpp
        src/map.h
        src/position.cpp
        src/position.h
        main.cpp game.cpp game.h)

target_link_libraries(terminal_game ncurses)