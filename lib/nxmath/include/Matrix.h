#pragma once

#include <array>
#include <cstddef>
#include <ostream>

template<size_t Rows, size_t Cols>
class Matrix {
public:

  Matrix() {
    setAllTo(0);
  }

  Matrix(bool shouldInit) {
    if (!shouldInit) return;

    setAllTo(0);
  }

  Matrix(const float (&values)[Rows][Cols]) {
    for (size_t i = 0; i < Rows; i++) {
      for (size_t j = 0; j < Cols; ++j) {
        data[i * Cols + j] = values[i][j];
      }
    }
  }

  bool isSquare() const {
    return Rows == Cols;
  }

  void setAllTo(float value) {
    for (size_t i = 0; i < count; ++i) {
      data[i] = value;
    }
  }

  float& operator()(size_t row, size_t col) {
    return data[row * Cols + col];
  }
  const float& operator()(size_t row, size_t col) const {
    return data[row * Cols + col];
  }
private:
  std::array<float, Rows * Cols> data {};
  const size_t count = Rows * Cols;
};

template<int Dim>
Matrix<Dim, Dim> identityMat() {
  Matrix<Dim, Dim> m;
  for (size_t i = 0; i < Dim; ++i) {
    for (size_t j = 0; j < Dim; ++j) {
      if (i == j) m(i, j) = 1;
    }
  }
  return m;
}

template<size_t Rows, size_t Cols>
std::ostream& operator<<(std::ostream& out, const Matrix<Rows, Cols> m) {
  out << "Matrix [\n";
  for (size_t i = 0; i < Rows; i++) {
    out << "  ";
    for (size_t j = 0; j < Cols; j++) {
      out << m(i, j) << ' ';
    }
    out << '\n';
  }
  out << "]\n";
  return out;
}