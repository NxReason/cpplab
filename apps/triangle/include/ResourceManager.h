#pragma once

#include "Graphics.h"
#include "Scene.h"
#include <unordered_map>

struct Mesh {
  VAO vao;
  VBO vbo;
  EBO ebo;
};

class ResourceManager {
private:
  static int id;
  std::unordered_map<int, Mesh> meshMap;

public:
  void generateResources(IScene* scene);
  Mesh getMesh(int meshKey);
};
