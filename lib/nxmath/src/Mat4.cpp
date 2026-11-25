#include "Mat4.h"

#include <array>
#include <cmath>
#include <iomanip>
#include <ios>

namespace nxmath {

Mat4::Mat4()
  : m_data{} { }

Mat4::Mat4(const std::array<float, 16>& data) {
  for (size_t row = 0; row < 4; row++) {
    for (size_t col = 0; col < 4; col++) {
      (*this)(row, col) = data[row * 4 + col];
    }
  }
}

float& Mat4::operator()(size_t row, size_t col) {
  return m_data[col * 4 + row];
}


const float& Mat4::operator()(size_t row, size_t col) const {
  return m_data[col * 4 + row];
}


const float* Mat4::data() const {
  return m_data;
}


Mat4 Mat4::operator*(const Mat4& other) const {
  Mat4 out;

  for (size_t r = 0; r < 4; ++r) {
    for (size_t c = 0; c < 4; ++c) {
      for (size_t i = 0; i < 4; ++i) {
        out(r, c) += (*this)(r, i) * other(i, c);
      }
    }
  }

  return out;
}


Mat4 Mat4::identity() {
  return Mat4 { std::array<float, 16> {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  }};
}

Mat4 Mat4::translation(const Vector3& value) {
  return Mat4 { std::array<float, 16> {
    1, 0, 0, value.x,
    0, 1, 0, value.y,
    0, 0, 1, value.z,
    0, 0, 0, 1
  }};
}

Mat4 Mat4::scaling(const Vector3& scale) {
  return Mat4 { std::array<float, 16> {
    scale.x, 0, 0, 0,
    0, scale.y, 0, 0,
    0, 0, scale.z, 0,
    0, 0, 0, 1
  }};
}

Mat4 Mat4::rotation_x(float angle) {
  float c = std::cos(angle);
  float s = std::sin(angle);

  return Mat4 { std::array<float, 16> {
    1, 0, 0, 0,
    0, c, -s, 0,
    0, s, c, 0,
    0, 0, 0, 1
  }};
}

Mat4 Mat4::rotation_y(float angle) {
  float c = std::cos(angle);
  float s = std::sin(angle);

  return Mat4 { std::array<float, 16> {
    c, 0, s, 0,
    0, 1, 0, 0,
    -s, 0, c, 0,
    0, 0, 0, 1
  }};
}

Mat4 Mat4::rotation_z(float angle) {
  float c = std::cos(angle);
  float s = std::sin(angle);

  return Mat4 { std::array<float, 16> {
    c, -s, 0, 0,
    s, c, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  }};
}

Mat4 Mat4::view(const Vector3& position, const Vector3& rotation) {
  return rotation_z(-rotation.z)
         * rotation_x(-rotation.x)
         * rotation_y(-rotation.y)
         * translation(-position);
}

Mat4 Mat4::ortho(float left, float right, float bottom, float top, float near, float far) {
  return Mat4 { std::array<float, 16> {
    2 / (right - left), 0, 0, -(right + left) / (right - left),
    0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom),
    0, 0, -2 / (far - near), -(far + near) / (far - near),
    0, 0, 0, 1
  }};
}

Mat4 Mat4::perspective(float fov, float aspect, float near, float far) {
  float q = 1 / std::tan(fov / 2);
  float a = -(far + near) / (far - near);
  float b = -2 * (far * near) / (far - near);
  return Mat4 { std::array<float, 16> {
    q / aspect, 0, 0, 0,
    0, q, 0, 0,
    0, 0, a, b,
    0, 0, -1, 0
  }};
}

/*
* Utils
*/
std::ostream& operator<<(std::ostream& out, const Mat4 mat) {
  out << "Mat4:\n";
  out << std::setprecision(3);
  for (size_t row = 0; row < 4; row++) {
    for (size_t col = 0; col < 4; col++) {
      out << mat(row, col) << ' ';
    }
    out << '\n';
  }
  out << std::defaultfloat << std::setprecision(6);
  return out;
}

}