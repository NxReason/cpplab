#pragma once

#include <vector>

#include "ISprite.h"
#include "Vector.h"

using nxmath::Vector3;

class Triangle : public ISprite {
public:
  Triangle(Vector3 a = { -0.5, -0.5 }, Vector3 b = { 0.5, -0.5 }, Vector3 c = { 0.0, 0.5 });

  std::vector<float> getCoords() const override;
  std::vector<unsigned int> getIndices() const override;
  int getVertexCount() const override;
private:
  Vector3 a;
  Vector3 b;
  Vector3 c;
};