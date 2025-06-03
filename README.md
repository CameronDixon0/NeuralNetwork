# NeuralNet

A simple neural network implementation in C++, inspired by 3Blue1Brown's [Deep Learning](https://www.youtube.com/playlist?list=PLZHQObOWTQDMsr9K-rj53DwVRMYO3t5Yr) series.

## Overview
This project demonstrates the fundamentals of neural networks, including forward and backward propagation, using the MNIST dataset for handwritten digit recognition. The code is designed for clarity and educational purposes, closely following the concepts and visualizations from 3Blue1Brown's videos.

## Features
- Feedforward neural network from scratch in C++
- Trains on the MNIST dataset
- Simple matrix math utilities
- Minimal dependencies

## Project Structure
- `main.cpp` — Entry point and training loop
- `nnet/` — Neural network and math utilities
- `mnist/` — MNIST dataset loader and files
- `build/` — Build artifacts (ignored by git)

## Getting Started
### Prerequisites
- C++17 or newer compiler (e.g., g++, clang++)
- CMake (for build management)

### Build Instructions
1. Clone the repository:
   ```sh
   git clone <repo-url>
   cd NeuralNet
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
