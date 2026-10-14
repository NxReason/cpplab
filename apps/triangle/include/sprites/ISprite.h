#pragma once

#include "Graphics.h"
#include "Vector.h"
#include <string>
#include <unordered_map>
#include <vector>

class ISprite {
public:
  std::string shaderName{ "default" };
  int meshName {};
  std::unordered_map<std::string, nxmath::Vector3> uniforms;

  virtual std::vector<float> getCoords() const = 0;
  virtual std::vector<unsigned int> getIndices() const = 0;
  virtual int getVertexCount() const = 0;
  virtual std::vector<VertexAttribute> getVAOLayout() const = 0;
};