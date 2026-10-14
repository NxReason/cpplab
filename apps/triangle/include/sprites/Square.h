#pragma once

#include "ISprite.h"
#include "Vector.h"

using nxmath::Vector3;

class Square : public ISprite {
public:
  Square(Vector3 pos = { 0.0f, 0.0f, 0.0f }, float sideWidth = 1.0);

  std::vector<float> getCoords() const override;
  std::vector<unsigned int> getIndices() const override;
  int getVertexCount() const override;
  std::vector<VertexAttribute> getVAOLayout() const override;
private:
  Vector3 pos;
  float sideWidth;
};