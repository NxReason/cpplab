#pragma once

class Vector {
public:
  Vector(float x = 0.0f, float y = 0.0f, float z = 0.0f);

  float x() const;
  float y() const;
  float z() const;
private:
  float m_x;
  float m_y;
  float m_z;
};

void print(const Vector& v);

void vectorEx();