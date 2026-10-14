#pragma once

#include <vector>

#include "ISprite.h"
#include "Vector.h"

using nxmath::Vector3;

class ColorTriangle : public ISprite {
public:
  ColorTriangle(Vector3 a = { -0.5, -0.5 }, Vector3 b = { 0.5, -0.5 }, Vector3 c = { 0.0, 0.5 });

  std::vector<float> getCoords() const override;
  std::vector<unsigned int> getIndices() const override;
  int getVertexCount() const override;
  std::vector<VertexAttribute> getVAOLayout() const override;

  void setColor(const std::string& hex);
private:
  Vector3 a;
  Vector3 b;
  Vector3 c;
  std::string colorHex;
};