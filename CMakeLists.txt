cmake_minimum_required(VERSION 2.6)

project(hex)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
#set(CMAKE_CXX_FLAGS "-g -Wall -O3 -std=c++11 -stdlib=libc++")
set(CMAKE_CXX_FLAGS "-g -Wall -O3 -std=c++11")

add_executable(hex main.cpp cli_hex.cpp game.cpp hexGraph.cpp subBoard.cpp monteCarloTreeSearch.cpp pureMonteCarlo.cpp humanPlayerCLI.cpp computerPlayer.cpp)
add_executable(testing test/test_ai.cpp game.cpp hexGraph.cpp subBoard.cpp computerPlayer.cpp pureMonteCarlo.cpp monteCarloTreeSearch.cpp)
