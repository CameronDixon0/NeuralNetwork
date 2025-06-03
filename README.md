# NeuralNet

A simple neural network implementation in C++, inspired by 3Blue1Brown's [Deep Learning](https://youtube.com/playlist?list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi&si=J-RySAsyjDbob1bH) series.

## Overview
I recently came across 3Blue1Brown's series on Deep Learning. This inspired me to implement my own Neural Network from scratch in C++.

## Features
- Feedforward neural network from scratch in C++
- Backpropogation using gradient descent
- Adjustable and flexible network sizes and shapes
- Simple custom linear algebra operations
- Trains on the MNIST dataset

## Project Structure
- `main.cpp` — Entry point and training loop
- `nnet/` — Neural network and math utilities
- `mnist/` — MNIST dataset loader and files

## Getting Started
### Prerequisites
- C++17 or newer compiler (e.g., g++, clang++)
- CMake (for build management)

### Build Instructions
1. Clone the repository:
   ```sh
   git clone https://github.com/CameronDixon0/NeuralNetwork
   cd NeuralNetwork
   ```
2. Build the project using CMake:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```
3. Run the executable:
   ```sh
   ./NeuralNet
   ```

### MNIST Dataset
The MNIST dataset files are expected in the `mnist/` directory. Download them from [Yann LeCun's website](http://yann.lecun.com/exdb/mnist/) if not already present.

## References
- [3Blue1Brown: Deep Learning](https://youtube.com/playlist?list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi&si=J-RySAsyjDbob1bH)
- [MNIST Database](http://yann.lecun.com/exdb/mnist/)

## License
MIT License
