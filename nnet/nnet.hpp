#include <iostream>
#include "nnet-math.hpp"

namespace nnet {

struct Layer {
  int size;
  Layer* input;
  Matrix weights;
  Vector biases;
  Vector values;

  Layer() : size(0), input(nullptr), weights(0, 0), biases(0), values(0){};

  Layer(int size, Layer* input = nullptr) : size(size), input(input), weights(size, input ? input->size : 0), biases(size), values(size, 0){};
};

struct Network {
  int numLayers;
  std::vector<Layer> layers;

  Network(std::vector<int> sizes) : numLayers(sizes.size()), layers(sizes.size()) {
    layers[0] = Layer(sizes[0], nullptr);
    for (int i = 1; i < sizes.size(); i++) {
      layers[i] = Layer(sizes[i], &layers[i - 1]);
    }
  };

  Network(std::ifstream& file) {
    file.read((char*) &numLayers, 4);
    layers.resize(numLayers);
    std::vector<int> sizes(numLayers, 0);
    for (int n = 0; n < numLayers; n++) {
      file.read((char*) &sizes[n], 4);
    }
    for (int n = 1; n < numLayers; n++) {
      Matrix weights(sizes[n], sizes[n - 1], 0);
      for (int i = 0; i < weights.m; i++) {
        for (int j = 0; j < weights.n; j++) {
          file.read((char*) &weights(i, j), 4);
        }
      }
      Vector biases(sizes[n], 0);
      for (int i = 0; i < biases.len; i++) {
        file.read((char*) &biases[i], 4);
      }
      layers[n].weights = weights;
      layers[n].biases = biases;
    }
  }

  Vector getOutput() {
    Vector output = layers[numLayers - 1].values;
    float denom = 0;
    for (int v = 0; v < output.len; v++) {
      denom += std::exp(output[v]);
    }
    for (int v = 0; v < output.len; v++) {
      output[v] = std::exp(output[v]) / denom;
    }
    return output;
  }

  void feedForward(Vector& inputs) {
    layers[0].values = inputs;
    for (int i = 1; i < numLayers; i++) {
      Vector input = layers[i - 1].values;
      for (int v = 0; v < input.len; v++) {
        input[v] = activation(input[v]);
      }
      layers[i].values = layers[i].weights * input + layers[i].biases;
    }
  }
  
  void backProp(Vector& expected, float learnRate) {
    Vector currentDerivative = getOutput() - expected;

    for (int layerNum = numLayers - 1; layerNum > 0; layerNum--) {

      // Get the current layer and the previous layer in the network
      Layer& layer = layers[layerNum];
      Vector& prevLayerValues = layers[layerNum - 1].values;

      float* layerWeights = layer.weights.data.data();
      int m = layer.weights.m;
      int n = layer.weights.n;

      if (layerNum != numLayers - 1) {
        for (int v = 0; v < currentDerivative.len; v++) {
          currentDerivative[v] *= activationDerivative(layer.values[v]);
        }
      }

      // Calculate the derivative of the next layer as a sum of the weights connecting it to the current layer
      Vector nextDerivative(layer.weights.n, 0);
      for (int j = 0; j < layer.weights.n; j++) {
        for (int i = 0; i < layer.weights.m; i++) {
          nextDerivative[j] += layerWeights[i * n + j] * currentDerivative[i]; 
        }
      }
  
      // Apply the activation function to each of the previous layer's outputs
      for (int v = 0; v < prevLayerValues.len; v++) {
        prevLayerValues[v] = activation(prevLayerValues[v]);
      }

      // Update current layer's biases
      float* layerBiases = layer.biases.data.data();
      for (int i = 0; i < currentDerivative.len; i++) {
        layerBiases[i] -= currentDerivative[i] * learnRate;
      }

      // Update current layer's weights
      for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
          layerWeights[i * n + j] -= prevLayerValues[j] * currentDerivative[i] * learnRate;
        }
      }

      currentDerivative = nextDerivative;
    }
  } 

  float activation(float x) {
    // return 1 / (1 + std::exp(-x));
    return (x > 0) ? x : 0;
  };

  float activationDerivative(float x) {
    // return std::exp(-x) / ((1 + std::exp(-x)) * (1 + std::exp(-x)));
    return (x > 0) ? 1 : 0;
  }

  float cost(Vector &expected) {
    float res = 0;
    Vector out = getOutput();
    for (int i = 0; i < expected.len; i++) {
      if (expected[i] == 1) {
        res -= std::log(out[i] + 1e-8);
      }
    }
    return res;
  }

  void saveToFile(std::ofstream& file) {
    file.write((char*) &numLayers, 4);
    for (int n = 0; n < numLayers; n++) {
      file.write((char*) &layers[n].size, 4);
    }
    for (int n = 1; n < numLayers; n++) {
      for (int i = 0; i < layers[n].weights.data.size(); i++) {
        file.write((char*) &layers[n].weights.data[i], 4);
      }
      for (int i = 0; i < layers[n].biases.len; i++) {
        file.write((char*) &layers[n].biases[i], 4);
      }
    }
  }

};



}