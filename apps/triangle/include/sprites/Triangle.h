#pragma once

#include <vector>

#include "ISprite.h"
#include "Vector.h"

using nxmath::Vector3;

class Triangle : public ISprite {
public:
  Triangle();
  Triangle(Vector3 a, Vector3 b, Vector3 c);

  std::vector<float> getCoords() const override;
  int getVertexCount() const override;
private:
  std::vector<float> coords = {};
};