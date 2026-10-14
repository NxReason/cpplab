#pragma once

#include "ISprite.h"
#include "NxMath.h"

class Square : public ISprite {
public:
  Square(Vector2 pos = { 0.0f, 0.0f }, float sideWidth = 0.3);

  std::vector<float> getCoords() const override;
  int getVertexCount() const override;
private:
  Vector2 pos;
  float sideWidth;
};