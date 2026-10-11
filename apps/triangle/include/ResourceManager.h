#pragma once

#include "Graphics.h"
#include "Scenes.h"
#include <unordered_map>

struct Mesh {
  VAO vao;
  VBO vbo;
};

class ResourceManager {
private:
  static int id;
  std::unordered_map<int, Mesh> meshMap;

public:
  void generateResources(TriangleScene scene);
  Mesh getMesh(int meshKey);
};
