cmake_minimum_required(VERSION 2.6)

project(hex)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
#set(CMAKE_CXX_FLAGS "-g -Wall -O3 -std=c++11 -stdlib=libc++")
set(CMAKE_CXX_FLAGS "-g -Wall -O3 -std=c++11")

add_executable(hex main.cpp cli_hex.cpp game.cpp hexGraph.cpp subBoard.cpp pureMonteCarloPlayer.cpp mcSearchTreePlayer.cpp)
add_executable(testing test/test.cpp cli_hex.cpp game.cpp hexGraph.cpp subBoard.cpp pureMonteCarloPlayer.cpp mcSearchTreePlayer.cpp)
