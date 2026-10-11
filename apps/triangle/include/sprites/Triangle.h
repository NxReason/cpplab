#pragma once

#include <vector>

#include "ISprite.h"
#include "NxMath.h"

class Triangle : public ISprite {
public:
  Triangle();
  Triangle(Vector2 a, Vector2 b, Vector2 c);

  std::vector<float> getCoords() const override;
  int getVertexCount() const override;
private:
  std::vector<float> coords = {};
};