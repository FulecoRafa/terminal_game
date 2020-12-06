cmake_minimum_required(VERSION 3.17)
project(terminal_game)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-lncurses")

include_directories(io/src)
include_directories(semaphore/src)
include_directories(src)
target_link_libraries(terminal_game ncurses)

add_executable(terminal_game
        io/src/input.cpp
        io/src/input.h
        io/src/io.h
        io/src/output.cpp
        io/src/output.h
        io/src/test.cpp
        io/src/test2.cpp
        semaphore/src/fulecoSimpleSemaphore.cpp
        semaphore/src/fulecoSimpleSemaphore.h
        semaphore/src/semTest.cpp
        src/character.cpp
        src/character.h
        src/item.cpp
        src/item.h
        src/main.cpp
        src/map.cpp
        src/map.h
        src/position.cpp
        src/position.h
        main.cpp)
