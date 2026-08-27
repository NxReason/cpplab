#pragma once

#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <utility>

#include "Vector.h"

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

  /*
  * Transpose
  */
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

  /*
  * Inverse
  */
  auto inverse() const requires(Rows == Cols) {
    // construct n*2n matrix with half copy + half identity
    Matrix<Rows, 2 * Rows> n2n{};
    for (size_t r = 0; r < Rows; ++r) {
      for (size_t c = 0; c < Cols; ++c) {
        n2n(r, c) = (*this)(r, c);
      }
      for (size_t c = 0; c < Cols; ++c) {
        if (r == c) n2n(r, c + Cols) = 1;
        else n2n(r, c + Cols) = 0;
      }
    }

    for (size_t c = 0; c < Cols; ++c) {
      // find the row with max value at column "c"
      float max = std::abs(n2n(c, c));
      size_t max_i = c;
      for (size_t r = c; r < Rows; ++r) {
        if (std::abs(n2n(r, c)) > max) {
          max = n2n(r, c);
          max_i = r;
        }
      }
      assert(max != 0);

      // swap the rows with the max value to the current one
      if (max_i != c) {
        n2n.swapRows(c, max_i);
      }

      // divide row by max value (sets current r,c = 1)
      size_t curRow = c;
      for (size_t col = 0; col < Cols * 2; ++col) {
        n2n(curRow, col) /= max;
      }

      // clear the rest of the column to 0
      for (size_t row = 0; row < Rows; ++row) {
        if (row == c) continue;
        float mult = -n2n(row, c);
        for (size_t col = 0; col < 2 * Cols; ++col) {

          n2n(row, col) += mult * n2n(c, col);
        }
      }
    }

    // construct output matrix from the right side of n2n
    Matrix<Rows, Cols> out{};
    for (size_t row = 0; row < Rows; ++row) {
      for (size_t col = 0; col < Cols; ++col) {
        out(row, col) = n2n(row, col + Cols);
      }
    }
    return out;
  }

  /*
  * Determinant
  */
  float determinant() const requires(Rows == Cols) {
    Matrix temp { *this };
    float det = 1.0f;
    constexpr float epsilon = 1e-6f;

    for (size_t col = 0; col < Cols; ++col) {
      // find pivot
      size_t pivot = col;
      for (size_t rp = col + 1; rp < Rows; ++rp) {
        if (std::abs(temp(rp, col)) > std::abs(temp(pivot, col))) pivot = rp;
      }

      // matrix is singular
      if (std::abs(temp(pivot, col)) < epsilon) return 0.0f;

      // swap rows if necessary
      if (pivot != col) {
        temp.swapRows(col, pivot);
        det = -det;
      }

      // eliminate below pivot
      const float p = temp(col, col);
      for (size_t er = col + 1; er < Rows; ++er) {
        const float factor = temp(er, col) / p;
        for (size_t ec = col + 1; ec < Cols; ++ec) {
          temp(er, ec) -= factor * temp(col, ec);
        }
      }

      det *= p;
    }

    return det;
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

  size_t getRowsNum() const {
    return Rows;
  }
  size_t getColsNum() const {
    return Cols;
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
  size_t count = Rows * Cols;
};

typedef Matrix<4, 4> Mat4;

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
* Vector multiplication
*/
Vector3 operator*(Mat4 m, Vector3 v);

/*
* Transformations
*/
Mat4 scale(float x, float y, float z = 1.0f);
Mat4 scale(float value);
Mat4 translate(float x, float y, float z = 1.0f);
Mat4 rotateX(float angleRad);
Mat4 rotateY(float angleRad);
Mat4 rotateZ(float angleRad);

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


/*
* Print to std::cout 
*/
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

}
