#pragma once

class Point2d {
public:
  Point2d();
  Point2d(double x, double y);

  void print() const;
  double distanceTo(const Point2d& other) const;
private:
  double m_x { 0.0 };
  double m_y { 0.0 };
};

void point2dEx();