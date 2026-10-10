#pragma once

#include "Scenes.h"
#include "Graphics.h"
#include "Shader.h"
#include <vector>

struct Viewport {
  int x;
  int y;
  int width;
  int height;
};

class Renderer {
public:
  Renderer();
  ~Renderer();
  void setClearColor();
  void render();
  void render(TriangleScene scene);
  void setViewport(Viewport size);
  void genBuffers(TriangleScene scene);

private:
  std::vector<VBO> vbos;
  std::vector<VAO> vaos;
  ShaderProgram program;
};