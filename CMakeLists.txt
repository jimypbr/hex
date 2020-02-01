cmake_minimum_required(VERSION 2.8)
project(hex)

option(USE_CLANG "build application with clang" ON)

# require C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-sign-compare -O3 -stdlib=libc++")


add_executable(hex main.cpp cli_hex.cpp game.cpp hexGraph.cpp subBoard.cpp monteCarloTreeSearch.cpp pureMonteCarlo.cpp humanPlayerCLI.cpp computerPlayer.cpp)
add_executable(testing test/test.cpp game.cpp hexGraph.cpp subBoard.cpp computerPlayer.cpp pureMonteCarlo.cpp monteCarloTreeSearch.cpp)
