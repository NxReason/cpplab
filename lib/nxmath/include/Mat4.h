#pragma once

#include <cstddef>
#include <array>
#include <iostream>

#include "Vector.h"

namespace nxmath {

class Mat4 {
public:
  Mat4();
  Mat4(const std::array<float, 16>& data);

  float& operator()(size_t row, size_t col);
  const float& operator()(size_t row, size_t col) const;

  const float* data() const;

  Mat4 operator*(const Mat4& other) const;

  static Mat4 identity();
  static Mat4 translation(const Vector3& value);
  static Mat4 scaling(const Vector3& scale);
  static Mat4 rotation_x(float angle);
  static Mat4 rotation_y(float angle);
  static Mat4 rotation_z(float angle);

  static Mat4 view(const Vector3& position, const Vector3& rotation);

  static Mat4 ortho(float left, float right, float bottom, float top, float near, float far);
  static Mat4 perspective(float fov, float aspect, float near, float far);
private:
  float m_data[16];
};

std::ostream& operator<<(std::ostream& out, const Mat4 mat);

}