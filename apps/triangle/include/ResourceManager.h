#pragma once

#include <unordered_map>

// #include "./graphics/GL.h"

struct Mesh {
  int id;
  // VAO vao;
  // VBO vbo;
  // EBO ebo;
};

class ResourceManager {
private:
  static int id;
  std::unordered_map<int, Mesh> meshMap;

public:
  void generateResources();
  Mesh getMesh(int meshKey);
};
