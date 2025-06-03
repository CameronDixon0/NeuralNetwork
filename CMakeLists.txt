cmake_minimum_required(VERSION 3.10)

project(NeuralNet)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")

add_executable(NeuralNet main.cpp)