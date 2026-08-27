cmake_minimum_required(VERSION 4.2)
project(gambit)

set(CMAKE_CXX_STANDARD 20)

add_executable(gambit main.cpp
        Board.cpp
        Board.h)
