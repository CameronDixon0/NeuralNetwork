#include <iostream>
#include <cstdlib>
#include <cassert>

namespace nnet {

struct Vector {
  int len;
  std::vector<float> data;
  Vector(int len, float defaultValue) : len(len), data(len, defaultValue){};
  Vector(int len) : len(len), data(len, 0){
    for (int i = 0; i < len; i++) {
      float r = rand() % 1000 / 10000.0;
      data[i] = r - 0.05;
    }
  };
  Vector(const std::vector<float>& vec) : len(vec.size()), data(vec){};

  float &operator[](int index) {
    return data[index];
  }

  Vector operator+(const Vector& other) {
    Vector res(len, 0);
    for (int i = 0; i < len; i++) {
      res[i] = data[i] + other.data[i];
    }
    return res;
  }

  Vector operator-(const Vector& other) {
    Vector res(len, 0);
    for (int i = 0; i < len; i++) {
      res[i] = data[i] - other.data[i];
    }
    return res;
  }

  Vector operator*(float mult) {
    Vector res(len, 0);
    for (int i = 0; i < len; i++) {
      res[i] = data[i] * mult;
    }
    return res;
  }
  
  float max() {
    float max = -__FLT_MAX__;
    for (int i = 0; i < len; i++) {
      if (data[i] > max) max = data[i];
    }
    return max;
  }
  float maxIndex() {
    float max = -__FLT_MAX__;
    int maxIndex = 0;
    for (int i = 0; i < len; i++) {
      if (data[i] > max) {
        max = data[i];
        maxIndex = i;
      }
    }
    return maxIndex;
  }
};

struct Matrix {
  int m;
  int n;
  std::vector<float> data;
  Matrix(int m, int n, float defaultValue) : m(m), n(n), data(m * n, defaultValue){};
  Matrix(int m, int n) : m(m), n(n), data(m * n, 0) {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        float r = std::rand() % 1000 / 10000.0;
        data[i * n + j] = r - 0.05;
      }
    }
  }
  Matrix(int m, int n, std::vector<float>& vec) : m(m), n(n), data(m * n, 0) {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        data[i * n + j] = vec[i * n + j];
      }
    }
  }

  float &operator()(int row, int col) {
    return data[row * n + col];
  }
  
  Vector operator*(Vector& vec) {
    Vector res(m, 0);
    float* dp = data.data();
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        res[i] += dp[i * n + j] * vec[j];
      }
    }
    return res;
  }
};

void _render(Matrix& m) {
  std::cout << "Dimensions: " << m.m << 'x' << m.n << '\n';
  for (int i = 0; i < m.m; i++) {
    for (int j = 0; j < m.n; j++) {
      std::cout << m(i, j) << ", ";
    }
      std::cout << "\n";
  }
}

void _render(Vector& v) {
  std::cout << "Length: " << v.len << '\n';
  for (int i = 0; i < v.len; i++) {
    std::cout << v[i] << '\n';
  }
}

}