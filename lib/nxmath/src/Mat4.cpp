#include "Mat4.h"
#include <cmath>

namespace nxmath {

Mat4::Mat4()
  : m_data{} { }

Mat4::Mat4(const std::vector<float>& data) {
  for (size_t i = 0; i < 16 && i < data.size(); i++) {
    m_data[i] = data[i];
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
  return Mat4 { std::vector<float> {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  }};
}

Mat4 Mat4::translation(const Vector3& value) {
  return Mat4 { std::vector<float> {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    value.x, value.y, value.z, 1
  }};
}

Mat4 Mat4::scaling(const Vector3& scale) {
  return Mat4 { std::vector<float> {
    scale.x, 0, 0, 0,
    0, scale.y, 0, 0,
    0, 0, scale.z, 0,
    0, 0, 0, 1
  }};
}

Mat4 Mat4::rotation_x(float angle) {
  float c = std::cos(angle);
  float s = std::sin(angle);

  return Mat4 { std::vector<float> {
    1, 0, 0, 0,
    0, c, -s, 0,
    0, s, c, 0,
    0, 0, 0, 1
  }};
}

Mat4 Mat4::rotation_y(float angle) {
  float c = std::cos(angle);
  float s = std::sin(angle);

  return Mat4 { std::vector<float> {
    c, 0, s, 0,
    0, 1, 0, 0,
    -s, 0, c, 0,
    0, 0, 0, 1
  }};
}

Mat4 Mat4::rotation_z(float angle) {
  float c = std::cos(angle);
  float s = std::sin(angle);

  return Mat4 { std::vector<float> {
    c, -s, 0, 0,
    s, c, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  }};
}

}