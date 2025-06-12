#include "nnet-math.h"
#include <iostream>
#include <cstdlib>  // for rand()

namespace nnet {

// ==================== Vector ====================

Vector::Vector(int len, float defaultValue) : len(len) {
  data = new float[len];
  for (int i = 0; i < len; i++) {
    data[i] = defaultValue;
  }
}

Vector::Vector(int len) : len(len) {
  data = new float[len];
  for (int i = 0; i < len; i++) {
    float r = rand() % 1000 / 10000.0;
    data[i] = r - 0.05;
  }
}

Vector::Vector(const std::vector<float>& vec) : len(vec.size()) {
  data = new float[len];
  for (int i = 0; i < vec.size(); i++) {
    data[i] = vec[i];
  }
}

Vector::~Vector() {
  delete[] data;
}

Vector::Vector(const Vector& other) : len(other.len) {
  data = new float[len];
  for (int i = 0; i < len; ++i) data[i] = other.data[i];
}

Vector& Vector::operator=(const Vector& other) {
  if (this == &other) return *this;
  delete[] data;
  len = other.len;
  data = new float[len];
  for (int i = 0; i < len; ++i) data[i] = other.data[i];
  return *this;
}

float& Vector::operator[](int index) const {
  return data[index];
}

Vector Vector::operator+(const Vector& other) const {
  Vector res(len, 0);
  for (int i = 0; i < len; i++) {
    res[i] = data[i] + other.data[i];
  }
  return res;
}

Vector Vector::operator-(const Vector& other) const {
  Vector res(len, 0);
  for (int i = 0; i < len; i++) {
    res[i] = data[i] - other.data[i];
  }
  return res;
}

Vector Vector::operator*(float mult) const {
  Vector res(len, 0);
  for (int i = 0; i < len; i++) {
    res[i] = data[i] * mult;
  }
  return res;
}

float Vector::max() {
  float maxVal = -__FLT_MAX__;
  for (int i = 0; i < len; i++) {
    if (data[i] > maxVal) maxVal = data[i];
  }
  return maxVal;
}

float Vector::maxIndex() {
  float maxVal = -__FLT_MAX__;
  int maxIdx = 0;
  for (int i = 0; i < len; i++) {
    if (data[i] > maxVal) {
      maxVal = data[i];
      maxIdx = i;
    }
  }
  return maxIdx;
}

// ==================== Matrix ====================

Matrix::Matrix(int m, int n, float defaultValue) : m(m), n(n) {
  data = new float[m * n];
  for (int i = 0; i < m * n; i++) {
    data[i] = defaultValue;
  }
}

Matrix::Matrix(int m, int n) : m(m), n(n) {
  data = new float[m * n];
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      float r = std::rand() % 1000 / 10000.0;
      data[i * n + j] = r - 0.05;
    }
  }
}

Matrix::Matrix(int m, int n, std::vector<float>& vec) : m(m), n(n) {
  data = new float[m * n];
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      data[i * n + j] = vec[i * n + j];
    }
  }
}

Matrix::~Matrix() {
  delete[] data;
}

Matrix::Matrix(const Matrix& other) : m(other.m), n(other.n) {
  data = new float[m * n];
  for (int i = 0; i < m * n; ++i) data[i] = other.data[i];
}

Matrix& Matrix::operator=(const Matrix& other) {
  if (this == &other) return *this;
  delete[] data;
  m = other.m;
  n = other.n;
  data = new float[m * n];
  for (int i = 0; i < m * n; ++i) data[i] = other.data[i];
  return *this;
}

float& Matrix::operator()(int row, int col) const {
  return data[row * n + col];
}

Vector Matrix::operator*(const Vector& vec) const {
  Vector res(m, 0);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      res[i] += data[i * n + j] * vec[j];
    }
  }
  return res;
}

// ==================== Functions ====================

void _render(const Matrix& mat) {
  std::cout << "Dimensions: " << mat.m << 'x' << mat.n << '\n';
  for (int i = 0; i < mat.m; i++) {
    for (int j = 0; j < mat.n; j++) {
      std::cout << mat(i, j) << ", ";
    }
    std::cout << '\n';
  }
}

void _render(const Vector& v) {
  std::cout << "Length: " << v.len << '\n';
  for (int i = 0; i < v.len; i++) {
    std::cout << v[i] << '\n';
  }
}

void mult(const Matrix& mat, const Vector& vec, Vector& out) {
  for (int i = 0; i < mat.m; i++) {
    for (int j = 0; j < mat.n; j++) {
      out.data[i] += mat(i, j) * vec[j];
    }
  }
}

} // namespace nnet
