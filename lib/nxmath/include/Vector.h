#pragma once

#include <array>
#include <iostream>

namespace nxmath {
  class Vector3 {
  public:
    Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

    float x;
    float y;
    float z;

    float length() const;
    void normalize();
    Vector3 proj(const Vector3& to) const;
    Vector3 perp(const Vector3& to) const;
  };

  float dot(const Vector3& left, const Vector3& right);
  Vector3 cross(const Vector3& left, const Vector3& right);
  Vector3 proj(const Vector3& from, const Vector3& to);
  Vector3 perp(const Vector3& from, const Vector3& to);

  Vector3 getNormalized(const Vector3& v);

  float getAngleRad(const Vector3& left, const Vector3& right);
  float getAngleDeg(const Vector3& left, const Vector3& right);

  bool isOrthogonal(const Vector3& left, const Vector3& right);
  bool isSameSide(const Vector3& left, const Vector3& right);

  std::array<Vector3, 3> orthogonalize(const Vector3& v1, const Vector3& v2, const Vector3& v3);

  Vector3 operator*(const Vector3& v, float s);
  Vector3 operator*(float s, const Vector3& v);
  Vector3 operator/(const Vector3& v, float s);
  Vector3 operator-(const Vector3& v);
  Vector3 operator+(const Vector3& left, const Vector3& right);
  Vector3 operator-(const Vector3& left, const Vector3& right);
  bool operator==(const Vector3& left, const Vector3& right);

  std::ostream& operator<<(std::ostream& out, const Vector3& v);
}
