#pragma once

#include "ResourceManager.h"
#include "Scenes.h"
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
  void render(ResourceManager& res_manager, const Scene* scene);
  void set_viewport(const Viewport& size);
  void set_polygon_mode(bool isOn);
private:
  ShaderProgram program;
};