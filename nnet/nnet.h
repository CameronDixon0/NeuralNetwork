#pragma once
#include <vector>
#include <fstream>
#include "nnet-math.h"

namespace nnet {

struct Layer {
  int size;
  Layer* input;
  Matrix weights;
  Vector biases;
  Vector values;
  Vector activatedValues;

  Layer(int size, Layer* input = nullptr);
};

struct Network {
  int numLayers;
  std::vector<Layer> layers;

  Network(std::vector<int> sizes);
  Network(std::ifstream& file);

  void feedForward(const Vector& inputs);
  void backProp(const Vector& expected, float learnRate);
  Vector getOutput();
  float cost(Vector& expected);
  void saveToFile(std::ofstream& file);

private:
  float activation(float x);
  float activationDerivative(float x);
};

}
