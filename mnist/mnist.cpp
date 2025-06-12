#include <iostream>
#include <fstream>
#include "./mnist.h"

namespace mnist {

// reverseInt function by mrgloom (https://stackoverflow.com/a/10409376)
int reverseInt (int i) {
  unsigned char c1, c2, c3, c4;
  c1 = i & 255;
  c2 = (i >> 8) & 255;
  c3 = (i >> 16) & 255;
  c4 = (i >> 24) & 255;
  return (static_cast<int>(c1) << 24) + (static_cast<int>(c2) << 16) + (static_cast<int>(c3) << 8) + c4;
}

void readInfo(std::ifstream& file) {
  if (file.is_open()) {
    int magicNumber = 0;
    int numImages = 0;
    int numRows = 0;
    int numColums = 0;
    file.read(reinterpret_cast<char*>(&magicNumber), sizeof(int)); 
    magicNumber = reverseInt(magicNumber);
    file.read(reinterpret_cast<char*>(&numImages), sizeof(int)); 
    numImages = reverseInt(numImages);
    file.read(reinterpret_cast<char*>(&numRows), sizeof(int)); 
    numRows = reverseInt(numRows);
    file.read(reinterpret_cast<char*>(&numColums), sizeof(int)); 
    numColums = reverseInt(numColums);
    std::cout << "Magic Number: " << magicNumber << '\n';
    std::cout << "Number of Images: " << numImages << '\n';
    std::cout << "Image Resolution: " << numColums << "x" << numRows << '\n';
  }
}

void readNumber(std::ifstream& file, std::vector<uint8_t>& number) {
  uint8_t buffer;
  for (size_t i = 0; i < 28; i++) {
    for (size_t j = 0; j < 28; j++) {
      file.read(reinterpret_cast<char*>(&buffer), 1);
      number[i * 28 + j] = buffer;
    }
  }
}

void readNumber(std::ifstream& file, std::vector<float>& number) {
  uint8_t buffer;
  for (size_t i = 0; i < 28; i++) {
    for (size_t j = 0; j < 28; j++) {
      file.read((char*)&buffer, 1);
      number[i * 28 + j] = (float) buffer / 255;
    }
  }
}

void readAllToVector(std::ifstream& file, std::vector<std::vector<float> >& vector) {
  int magicNumber = 0;
  int numImages = 0;
  int numRows = 0;
  int numColums = 0;
  file.read(reinterpret_cast<char*>(&magicNumber), sizeof(int)); 
  magicNumber = reverseInt(magicNumber);
  file.read(reinterpret_cast<char*>(&numImages), sizeof(int)); 
  numImages = reverseInt(numImages);
  file.read(reinterpret_cast<char*>(&numRows), sizeof(int)); 
  numRows = reverseInt(numRows);
  file.read(reinterpret_cast<char*>(&numColums), sizeof(int)); 
  numColums = reverseInt(numColums);

  vector.resize(numImages);

  uint8_t buffer;
  for (size_t n = 0; n < numImages; n++) {
    std::vector<float>& number = vector[n];
    vector[n].resize(numRows * numColums);
    for (size_t i = 0; i < numRows; i++) {
      for (size_t j = 0; j < numColums; j++) {
        file.read((char*)&buffer, 1);
        number[i * numColums + j] = (float) buffer / 255;
      }
    }
  }
}

void readLabelsToVector(std::ifstream& file, std::vector<int>& vector) {
  int magicNumber = 0;
  int numImages = 0;
  file.read(reinterpret_cast<char*>(&magicNumber), sizeof(int)); 
  magicNumber = reverseInt(magicNumber);
  file.read(reinterpret_cast<char*>(&numImages), sizeof(int)); 
  numImages = reverseInt(numImages);

  vector.resize(numImages);

  uint8_t buffer;
  for (size_t n = 0; n < numImages; n++) {
    file.read((char*)&buffer, 1);
    vector[n] = (int) buffer;
  }
}

void renderNumber(std::vector<uint8_t>& number) {
  const char vals[] = {'`', '.', ',', '-', '~', ':', 'o','@'};
  for (size_t i = 0; i < 28; i++) {
    for (size_t j = 0; j < 28; j++) {
      uint8_t &pixel = number[i * 28 + j];
      if (pixel == 0) {
        std::cout << " ";
        continue;
      }
      for (size_t b = 0; b < 8; b++) {
        if (((0b10000000 >> b) & pixel) != 0) {
          std::cout << vals[7-b];
          break;
        }
      }
    }
    std::cout << '\n';
  }
}

void renderNumber(std::vector<float>& number) {
  const char vals[] = {'`', '.', ',', '-', '~', ':', 'o','@'};
  for (size_t i = 0; i < 28; i++) {
    for (size_t j = 0; j < 28; j++) {
      uint8_t pixel = number[i * 28 + j] * 255;
      if (pixel == 0) {
        std::cout << " ";
        continue;
      }
      for (size_t b = 0; b < 8; b++) {
        if (((0b10000000 >> b) & pixel) != 0) {
          std::cout << vals[7-b];
          break;
        }
      }
    }
    std::cout << '\n';
  }
}

}
