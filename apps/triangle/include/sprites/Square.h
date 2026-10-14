#pragma once

#include "ISprite.h"

#include "Vector.h"

using nxmath::Vector3;

class Square : public ISprite {
public:
  Square(Vector3 pos = { 0.0f, 0.0f, 0.0f }, float sideWidth = 0.3);

  std::vector<float> getCoords() const override;
  int getVertexCount() const override;
private:
  Vector3 pos;
  float sideWidth;
};