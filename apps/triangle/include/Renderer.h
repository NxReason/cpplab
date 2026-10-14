#pragma once

#include "ResourceManager.h"
#include "Scene.h"
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
  void render(IScene* scene);
  void setViewport(const Viewport& size);

  void generateResources(IScene* scene);
private:
  ResourceManager resourceManager;
  ShaderManager shaderManager;
};