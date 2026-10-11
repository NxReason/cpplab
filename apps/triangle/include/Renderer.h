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
  void setClearColor();
  void render(TriangleScene scene);
  void setViewport(Viewport size);

  void generateResources(TriangleScene scene);
private:
  ResourceManager resourceManager;
  ShaderManager shaderManager;
};