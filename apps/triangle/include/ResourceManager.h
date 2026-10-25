#pragma once

#include <unordered_map>

#include "graphics/GL.h"
#include "Scenes.h"

struct Mesh {
  VAO vao;
  VBO vbo;
  EBO ebo;
};

class ResourceManager {
private:
  static int id;
  std::unordered_map<int, Mesh> mesh_map;

public:
  void gen_resources(const Scene* scene);
  Mesh get_mesh(int mesh_key);
};
