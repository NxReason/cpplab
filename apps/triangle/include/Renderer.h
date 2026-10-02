#pragma once

#include "Shader.h"
#include "Viewport.h"

class Renderer {
public:
  Renderer();
  ~Renderer();
  void setClearColor();
  void render();
  void setViewport(Viewport size);

private:
  GLuint shader;
  GLuint vbo;
  GLuint vao;
};