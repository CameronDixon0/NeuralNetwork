#pragma once

#include <vector>

namespace nnet {

struct Vector {
  int len;
  float* data;

  Vector(int len, float defaultValue);
  Vector(int len);

  Vector(const std::vector<float>& vec);
  ~Vector();
  Vector(const Vector& other);
  Vector& operator=(const Vector& other);

  float& operator[](int index) const;

  Vector operator+(const Vector& other) const;
  Vector operator-(const Vector& other) const;
  Vector operator*(float mult) const;

  float max();
  float maxIndex();
};

struct Matrix {
  int m;
  int n;
  float* data;

  Matrix(int m, int n, float defaultValue);
  Matrix(int m, int n);
  Matrix(int m, int n, std::vector<float>& vec);

  ~Matrix();
  Matrix(const Matrix& other);
  Matrix& operator=(const Matrix& other);

  float& operator()(int row, int col) const;

  Vector operator*(const Vector& vec) const;
};

void _render(const Matrix& m);
void _render(const Vector& v);
void mult(const Matrix& mat, const Vector& vec, Vector& out);

} // namespace nnet
