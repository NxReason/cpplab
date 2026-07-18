#include "Vector.h"
#include <iostream>

Vector::Vector(float x, float y, float z)
  : m_x(x), m_y(y), m_z(z) {}

float Vector::x() const { return m_x; }
float Vector::y() const { return m_y; }
float Vector::z() const { return m_z; }

void print(const Vector& v) {
  std::cout << "Vector(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
}

void vectorEx() {
  Vector v{};
  print(v);
}