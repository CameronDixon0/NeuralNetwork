cmake_minimum_required(VERSION 3.10)

project(NeuralNet)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -march=native")
add_compile_options(-Wall -Wextra -pedantic)

add_executable(NeuralNet
  main.cpp
  mnist/mnist.cpp
  nnet/nnet.cpp
  nnet/nnet-math.cpp
)
