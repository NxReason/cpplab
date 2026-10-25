#pragma once

#include "graphics/GL.h"
#include "ResourceManager.h"
#include "Shader.h"

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
  void clear_color();
  void render();
  void set_viewport(const Viewport& size);
  void set_polygon_mode(bool isOn);

  void gen_resources();
private:
  ShaderProgram program;
  VAO vao;
  ResourceManager resource_manager;
};