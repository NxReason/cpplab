#pragma once

#include <vector>

#include "Mat4.h"
#include "Vector.h"
#include "Sprites.h"
#include "graphics/Shader.h"

using nxmath::Vector3;
using nxmath::Mat4;

struct Viewport {
  int x;
  int y;
  int width;
  int height;
};

class Scene {
public:
  std::vector<Sprite*> sprites;
  ShaderProgram program;

  virtual void clear_color();
  virtual void render();
  virtual void set_viewport(const Viewport& size);
  virtual void set_polygon_mode(bool is_on);
};

class TriangleScene : public Scene {
public:
  TriangleScene() {
    program.create("default");
    sprites.push_back(new Triangle);
  };
};

class RectangleScene : public Scene {
public:
  RectangleScene() {
    program.create("default");
    sprites.push_back(new Rectangle);
  }
};

class SandboxScene : public Scene {
public:
  SandboxScene() {
    program.create("anim");
    program.use();

    Mat4 model = Mat4::identity();
    model = Mat4::translation(Vector3{ 0.5, 0.5 })
      * Mat4::rotation_y(0.79)
      * Mat4::scaling(Vector3 { 1.0, 1.0, 1.0 });

    program.setUniform("transform", model);
    sprites.push_back(new Rectangle);
  }
};