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

  Vector3 Vector3::proj(const Vector3& to) const {
    float toLength = to.length();
    return dot(*this, to) * to / (toLength * toLength);
  }

  Vector3 Vector3::perp(const Vector3& to) const {
    Vector3 p = proj(to);
    return *this - p;
  }

  /*
  * non-class functions 
  */
  Vector3 getNormalized(const Vector3& v) {
    float len = v.length();
    if (len == 0) return Vector3 { 1.0 };
    return Vector3 { v.x / len, v.y / len, v.z / len };
  }

  float dot(const Vector3& left, const Vector3& right) {
    return left.x * right.x + left.y * right.y + left.z * right.z;
  }

  Vector3 cross(const Vector3& l, const Vector3& r) {
    return Vector3(l.y * r.z - l.z * r.y, l.z * r.x - l.x * r.z, l.x * r.y - l.y * r.x);
  }

  Vector3 proj(const Vector3& from, const Vector3& to) {
    return from.proj(to);
  }

  Vector3 perp(const Vector3& from, const Vector3& to) {
    return from.perp(to);
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

  std::array<Vector3, 3> orthogonalize(const Vector3& v1, const Vector3& v2, const Vector3& v3) {
    auto u2 = perp(v2, v1);
    auto u3 = perp(
      perp(v3, v1),
      u2
    );
    return std::array<Vector3, 3> { v1, u2, u3 };
  }

  /*
  * overloads
  */
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
  bool operator==(const Vector3& left, const Vector3& right) {
    return left.x == right.x && left.y == right.y && left.z == right.z;
  }

  std::ostream& operator<<(std::ostream& out, const Vector3& v) {
    out << "Vector3 (" << v.x << ", " << v.y << ", " << v.z << ")";
    return out;
  }
}
