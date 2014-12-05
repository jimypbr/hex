cmake_minimum_required(VERSION 2.6)

project(hex)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

add_executable(hex main.cpp cli_hex.cpp game.cpp hexGraph.cpp aiPlayer.cpp)
