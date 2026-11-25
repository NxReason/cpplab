#pragma once

#include <cstddef>
#include <vector>
#include "Vector.h"

namespace nxmath {

class Mat4 {
public:
  Mat4();
  Mat4(const std::vector<float>& data);

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
private:
  float m_data[16];
};

}