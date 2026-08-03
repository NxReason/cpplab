#include <cmath>
#include <cmath>
#include <numbers>
#include "Vector.h"

namespace nxmath {
  Vector3::Vector3(float x, float y, float z)
    : x { x }, y { y }, z { z } {}

  float Vector3::length() const {
    return std::sqrt(x * x + y * y + z * z);
  }

  void Vector3::normalize() {
    float len = length();
    if (len == 0) return;
    x = x / len;
    y = y / len;
    z = z / len;
  }

  Vector3 Vector3::proj(const Vector3& to) {
    return dot(*this, to) * to / to.length();
  }

  Vector3 getNormalized(const Vector3& v) {
    float len = v.length();
    if (len == 0) return Vector3 { 1.0 };
    return Vector3 { v.x / len, v.y / len, v.z / len };
  }

  float dot(const Vector3& left, const Vector3& right) {
    return left.x * right.x + left.y * right.y + left.z * right.z;
  }

  float getAngleRad(const Vector3& left, const Vector3& right) {
    float dotProd = dot(left, right);
    float cos = dotProd / (left.length() * right.length());
    return std::acos(cos);
  }

  float getAngleDeg(const Vector3& left, const Vector3& right) {
    return getAngleRad(left, right) * 180 / std::numbers::pi;
  }

  bool isOrthogonal(const Vector3& left, const Vector3& right) {
    return dot(left, right) == 0;
  }

  bool isSameSide(const Vector3& left, const Vector3& right) {
    return dot(left, right) > 0;
  }

  Vector3 operator*(const Vector3& v, float s) {
    return Vector3 { v.x * s, v.y * s, v.z * s };
  }
  Vector3 operator*(float s, const Vector3& v) { return v * s; }

  Vector3 operator/(const Vector3& v, float s) {
    return Vector3 { v.x / s, v.y / s, v.z / s };
  }

  Vector3 operator-(const Vector3& v) {
    return Vector3 { -v.x, -v.y, -v.z };
  }

  Vector3 operator+(const Vector3& left, const Vector3& right) {
    return Vector3 { left.x + right.x, left.y + right.y, left.z + right.z };
  }

  Vector3 operator-(const Vector3& left, const Vector3& right) {
    return Vector3 { left.x - right.x, left.y - right.y, left.z - right.z };
  }

  std::ostream& operator<<(std::ostream& out, const Vector3& v) {
    out << "Vector3 (" << v.x << ", " << v.y << ", " << v.z << ")";
    return out;
  }
}
