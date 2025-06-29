#include <iostream>
#include "mnist/mnist.h"
#include <fstream>
#include "nnet/nnet.h"

int main () {
  std::system("clear");

  std::ifstream trainingImages ("../mnist/mnist/train-images-idx3-ubyte");
  std::vector<std::vector<float> > numbers;
  mnist::readAllToVector(trainingImages, numbers);
  trainingImages.close();
 
  std::ifstream trainingLabels ("../mnist/mnist/train-labels-idx1-ubyte");
  std::vector<int> labels;
  mnist::readLabelsToVector(trainingLabels, labels);
  trainingLabels.close(); 

  nnet::Network net({784, 16, 16, 100});
  for (int iteration = 0; iteration < 100; iteration++) {
    std::cout << "Iteration " << iteration + 1 << std::endl;
    for (int i = 0; i < 60000; i++) {
      std::vector<float>& num = numbers[i];
      nnet::Vector vec(num);
 
      int label = labels[i];
 
      net.feedForward(vec);
 
      nnet::Vector expected(10, 0);
      expected[label] = 1;
      net.backProp(expected, 0.005 / (iteration + 1));
    }
  }
 
  std::ofstream outFile ("/Users/camerondixon/Development/Projects/C++/NeuralNet/trainedNetwork", std::ios::binary);
  net.saveToFile(outFile);
  outFile.close();

  std::ifstream testNumbersFile ("../mnist/mnist/t10k-images-idx3-ubyte");
  std::vector<std::vector<float>> testNumbers;
  mnist::readAllToVector(testNumbersFile, testNumbers);
  testNumbersFile.close();
 
  std::ifstream testLabelsFile ("../mnist/mnist/t10k-labels-idx1-ubyte");
  std::vector<int> testLabels;
  mnist::readLabelsToVector(testLabelsFile, testLabels);
  testLabelsFile.close();
 
  std::ifstream networkFile ("../trainedNetwork");
  nnet::Network testNet (networkFile);
  networkFile.close();
 
  int correct = 0;
  for (int i = 0; i < 10000; i++) {
    std::vector<float>& num = testNumbers[i];
    nnet::Vector vec(num);
    int label = testLabels[i];

    testNet.feedForward(vec);
 
    nnet::Vector output = testNet.getOutput();
    if (output.maxIndex() == label) correct++;
  }
  std::cout << "Accuracy: " << (float) correct / 100 << '%';

  return 0;
}
