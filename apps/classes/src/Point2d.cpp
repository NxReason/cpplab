#include "Point2d.h"
#include <cmath>
#include <iostream>

Point2d::Point2d()
  : m_x { 0.0 }, m_y { 0.0 } {}
Point2d::Point2d(double x, double y)
  : m_x { x }, m_y { y } {}

double Point2d::distanceTo(const Point2d& other) const {
  return std::sqrt(
    (m_x - other.m_x) * (m_x - other.m_x) +
    (m_y - other.m_y) * (m_y - other.m_y)
  );
}

void Point2d::print() const {
  std::cout << "Point2d(" << m_x << ", " << m_y << ")\n";
}

void point2dEx() {
  Point2d first{};
  Point2d second{ 3.0, 4.0 };
  // Point2d third { 4.0 };

  first.print();
  second.print();

  std::cout << "Distance between 2 points: " << first.distanceTo(second) << '\n';
}