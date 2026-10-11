#pragma once

#include <string>
#include <vector>

class ISprite {
public:
  std::string shaderName{ "default" };
  int meshName {};

  virtual std::vector<float> getCoords() const = 0;
  virtual int getVertexCount() const = 0;
};