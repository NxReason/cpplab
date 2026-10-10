#pragma once

#include <vector>

#include "NxMath.h"
#include "Graphics.h"

class Triangle {
public:
  Triangle();
  Triangle(Vector2 a, Vector2 b, Vector2 c);

  std::vector<float> getCoords() const;
  std::vector<VertexAttribute> getAttributeLayout() const;

private:
  std::vector<float> coords = {};
};