#pragma once

#include <vector>
#include "sprites/Triangle.h"

class IScene {
public:
  virtual std::vector<Triangle> getTriangles() const;
};

class TriangleScene {
public:
  TriangleScene();

  std::vector<Triangle> getTriangles() const;
private:
  std::vector<Triangle> triangles;
};