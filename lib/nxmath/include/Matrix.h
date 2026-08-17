#pragma once

#include <array>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <utility>

namespace nxmath {

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

  Matrix(float initialValue) {
    setAllTo(initialValue);
  }

  Matrix(const float (&values)[Rows][Cols]) {
    for (size_t i = 0; i < Rows; i++) {
      for (size_t j = 0; j < Cols; ++j) {
        data[i * Cols + j] = values[i][j];
      }
    }
  }

  Matrix<Cols, Rows> transpose() const {
    Matrix<Cols, Rows> out;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        out(j, i) = (*this)(i, j);
      }
    }
    return out;
  }

  template <size_t R = Rows, size_t C = Cols>
  requires (R == C)
  void transposeSelf() {
    for (size_t r = 0; r < Rows; ++r) {
      for (size_t c = r + 1; c < Cols; ++c) {
        std::swap((*this)(r, c), (*this)(c, r));
      }
    }
  }

  // utility
  bool isSquare() const {
    return Rows == Cols;
  }

  bool isDiagonal() const {
    if (!isSquare()) return false;

    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        if (i == j) continue;
        if ((*this)(i, j) != 0) return false;
      }
    }
    return true;
  }

  void setAllTo(float value) {
    for (size_t i = 0; i < count; ++i) {
      data[i] = value;
    }
  }

  void swapRows(size_t x, size_t y) {
    for (size_t c = 0; c < Cols; ++c) {
      std::swap((*this)(x, c), (*this)(y, c));
    }
  }

  size_t getCount() const {
    return count;
  }

  std::pair<size_t, size_t> getShape() const {
    return std::pair{ Rows, Cols };
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

/*
* Scalar multiplication
*/
template<size_t Rows, size_t Cols>
Matrix<Rows, Cols> operator*(const Matrix<Rows, Cols>& m, float s) {
  Matrix<Rows, Cols> out { m };
  for (size_t r = 0; r < Rows; ++r) {
    for (size_t c = 0; c < Cols; ++c) {
      out(r, c) = out(r, c) * s;
    }
  }
  return out;
}
template<size_t Rows, size_t Cols>
Matrix<Rows, Cols> operator*(float s, Matrix<Rows, Cols> m) {
  return m * s;
}

/*
* Matrix addition
*/
template <size_t R, size_t C>
Matrix<R, C> operator+(const Matrix<R, C>& left, const Matrix<R, C>& right) {
  Matrix<R, C> out;
  for (size_t r = 0; r < R; r++) {
    for (size_t c = 0; c < C; c++) {
      out(r, c) = left(r, c) + right(r, c);
    }
  }
  return out;
}

/*
* Matrix multiplication
*/
template <size_t RL, size_t CL, size_t RR, size_t CR>
requires(CL == RR)
Matrix<RL, CR> operator*(Matrix<RL, CL> left, Matrix<RR, CR> right) {
  Matrix<RL, CR> out;

  for (size_t r = 0; r < RL; ++r) {
    for (size_t c = 0; c < CR; ++c) {
      for (size_t i = 0; i < CL; ++i) {
        out(r, c) += left(r, i) * right(i, c);
      }
    }
  }

  return out;
}

/*
* Linear system
*/
template <size_t R, size_t C>
Matrix<R, C> linearSystem(const Matrix<R, C>& m) {
  Matrix<R, C> out { m };
  size_t i { 0 }, j { 0 };
  for (; i < R && j < C; ++i, ++j) {
    float max { out(i, j) };
    size_t max_idx { i };
    for (size_t k = i; k < R; ++k) {
      if (out(k, j) > max) { 
        max = out(k, j);
        max_idx = k;
      }
    }
    if (max == 0.0f) continue;

    if (max_idx != i) {
      out.swapRows(i, max_idx);
    }

    float div = out(i, j);
    for (size_t t = j; t < C; ++t) {
      out(i, t) = out(i, t) / div;
    }

    for (size_t rt = 0; rt < R; ++rt) {
      if (rt == i) continue;

      float coef = -out(rt, j);
      for (size_t ct = 0; ct < C; ++ct) {
        out(rt, ct) += coef * out(i, ct);
      }
    }
  }
  return out;
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

typedef Matrix<4, 4> Mat4;
}