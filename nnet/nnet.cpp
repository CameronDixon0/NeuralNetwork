#include "nnet.h"
#include <cmath> // for std::exp, std::log

namespace nnet {

// ======== Layer Constructor ========
Layer::Layer(int size, Layer* input)
  : size(size),
    input(input),
    weights(size, input ? input->size : 0),
    biases(size),
    values(size, 0),
    activatedValues(size, 0) {}


// ======== Network Constructors ========
Network::Network(std::vector<int> sizes) : numLayers(sizes.size()), layers() {
  layers.push_back(Layer(sizes[0], nullptr));
  for (int i = 1; i < sizes.size(); i++) {
    layers.push_back(Layer(sizes[i], &layers[i - 1]));
  }
}

Network::Network(std::ifstream& file) {
  file.read((char*)&numLayers, sizeof(int));
  std::vector<int> sizes(numLayers);
  for (int n = 0; n < numLayers; n++) {
    file.read((char*)&sizes[n], sizeof(int));
  }
  layers.push_back(Layer(sizes[0]));
  for (int n = 1; n < numLayers; n++) {
    layers.push_back(Layer(sizes[n]));
    Matrix weights(sizes[n], sizes[n - 1], 0);
    for (int i = 0; i < weights.m; i++) {
      for (int j = 0; j < weights.n; j++) {
        file.read((char*)&weights(i, j), sizeof(float));
      }
    }
    Vector biases(sizes[n], 0);
    for (int i = 0; i < biases.len; i++) {
      file.read((char*)&biases[i], sizeof(float));
    }
    layers[n].weights = weights;
    layers[n].biases = biases;
  }
}


// ======== Feedforward ========
void Network::feedForward(const Vector& inputs) {
  layers[0].values = inputs;
  layers[0].activatedValues = inputs;
  for (int i = 1; i < numLayers; i++) {
    Layer& prev = layers[i - 1];
    Layer& curr = layers[i];
    curr.values = curr.weights * prev.activatedValues + curr.biases;
    for (int n = 0; n < curr.size; n++) {
      curr.activatedValues[n] = activation(curr.values[n]);
    }
  }
}


// ======== Softmax Output ========
Vector Network::getOutput() {
  Vector output = layers[numLayers - 1].values;
  float denom = 0;
  for (int i = 0; i < output.len; i++) {
    denom += std::exp(output[i]);
  }
  for (int i = 0; i < output.len; i++) {
    output[i] = std::exp(output[i]) / denom;
  }
  return output;
}


// ======== Backpropagation ========
void Network::backProp(const Vector& expected, float learnRate) {
  Vector currentDerivative = getOutput() - expected;

  for (int layerNum = numLayers - 1; layerNum > 0; layerNum--) {
    Layer& layer = layers[layerNum];
    Vector& prevValues = layers[layerNum - 1].values;

    int m = layer.weights.m;
    int n = layer.weights.n;
    float* layerWeights = layer.weights.data;

    if (layerNum != numLayers - 1) {
      for (int i = 0; i < currentDerivative.len; i++) {
        currentDerivative[i] *= activationDerivative(layer.values[i]);
      }
    }

    // Calculate derivative for previous layer
    Vector nextDerivative(n, 0);
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        nextDerivative[j] += layerWeights[i * n + j] * currentDerivative[i];
      }
    }

    // Update biases
    float* layerBiases = layer.biases.data;
    for (int i = 0; i < m; i++) {
      layerBiases[i] -= currentDerivative[i] * learnRate;
    }

    // Update weights
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        layerWeights[i * n + j] -= prevValues[j] * currentDerivative[i] * learnRate;
      }
    }

    currentDerivative = nextDerivative;
  }
}


// ======== Loss / Cost ========
float Network::cost(Vector& expected) {
  float result = 0;
  Vector output = getOutput();
  for (int i = 0; i < expected.len; i++) {
    if (expected[i] == 1) {
      result -= std::log(output[i] + 1e-8);
    }
  }
  return result;
}


// ======== Save Network to File ========
void Network::saveToFile(std::ofstream& file) {
  file.write((char*)&numLayers, sizeof(int));
  for (int i = 0; i < numLayers; i++) {
    file.write((char*)&layers[i].size, sizeof(int));
  }

  for (int n = 1; n < numLayers; n++) {
    Layer& layer = layers[n];
    for (int i = 0; i < layer.weights.m * layer.weights.n; i++) {
      file.write((char*)&layer.weights.data[i], sizeof(float));
    }
    for (int i = 0; i < layer.biases.len; i++) {
      file.write((char*)&layer.biases[i], sizeof(float));
    }
  }
}


// ======== Activation Functions ========
float Network::activation(float x) {
  // ReLU
  return (x > 0) ? x : 0;
}

float Network::activationDerivative(float x) {
  // Derivative of ReLU
  return (x > 0) ? 1 : 0;
}

} // namespace nnet
