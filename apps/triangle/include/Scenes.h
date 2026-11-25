#pragma once

#include <vector>

#include "nxmath.h"
#include "Mat4.h"
#include "Sprites.h"
#include "graphics/Shader.h"

using namespace nxmath;

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
  Viewport viewport;

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

class OrthoScene : public Scene {
public:
  OrthoScene() {
    glEnable(GL_DEPTH_TEST);

    program.create("anim");
    program.use();

    Mat4 model = Mat4::identity();
    model = Mat4::translation(Vector3{ 200, 200, 0.0 });
    //   * Mat4::rotation_z(deg_to_rad(45))
    //   * Mat4::scaling(Vector3 { 1.0, 1.0, 1.0 });

    Vector3 camera_pos { 0, 0, 0.5 };
    Vector3 camera_rotation { 0, 0, 0 };
    Mat4 view = Mat4::view(camera_pos, camera_rotation);

    // viewport 1071, 800
    Mat4 proj = Mat4::ortho(0, 1071, 800, 0, 0.1, 100.0);

    program.setUniform("model", model);
    program.setUniform("view", view);
    program.setUniform("projection", proj);

    sprites.push_back(new Rectangle { 100 });
  }
};

class SandboxScene : public Scene {
public:
  SandboxScene() {
    glEnable(GL_DEPTH_TEST);

    program.create("anim");
    program.use();

    Mat4 model = Mat4::identity();
    model = Mat4::translation(Vector3{ 0, 0, 0 })
      * Mat4::rotation_y(deg_to_rad(45));
    //   * Mat4::scaling(Vector3 { 1.0, 1.0, 1.0 });

    Vector3 camera_pos { 0, 0, 20 };
    Vector3 camera_rotation { 0, 0, 0 };
    Mat4 view = Mat4::view(camera_pos, camera_rotation);

    // viewport 1071, 800
    float aspect = static_cast<float>(1071) / 800;
    Mat4 proj = Mat4::perspective(deg_to_rad(45), aspect, 0.1f, 100.f);

    program.setUniform("model", model);
    program.setUniform("view", view);
    program.setUniform("projection", proj);

    sprites.push_back(new Rectangle { 5, 2 });
  }
};
