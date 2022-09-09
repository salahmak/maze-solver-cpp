cmake_minimum_required(VERSION 3.24)
project(path_search)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/maze.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(path_search
        main.cpp
        Maze.cpp
        Maze.h
        Node.cpp
        Node.h
        StackFrontier.cpp
        StackFrontier.h
        QueueFrontier.cpp
        )
