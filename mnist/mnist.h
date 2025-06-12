#pragma once

#include <fstream>

namespace mnist {

int reverseInt(int i);
void readInfo(std::ifstream& file);
void readNumber(std::ifstream& file, std::vector<uint8_t>& number);
void readNumber(std::ifstream& file, std::vector<float>& number);
void readAllToVector(std::ifstream& file, std::vector<std::vector<float> >& vector);
void readLabelsToVector(std::ifstream& file, std::vector<int>& vector);
void renderNumber(std::vector<uint8_t>& number);
void renderNumber(std::vector<float>& number);

}
