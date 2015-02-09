cmake_minimum_required(VERSION 2.6)

project(hex)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-g -Wall -O3 -std=c++11 -stdlib=libc++")

add_executable(hex main.cpp cli_hex.cpp game.cpp hexGraph.cpp pureMonteCarlo.cpp)
