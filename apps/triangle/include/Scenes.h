#pragma once

#include "Sprites.h"
#include <vector>

class Scene {
public:
  std::vector<Sprite*> sprites;
};

class TriangleScene : public Scene {
public:
  TriangleScene() {
    sprites.push_back(new Triangle{});
  }
};

class RectangleScene : public Scene {
public:
  RectangleScene() {
    sprites.push_back(new Rectangle {});
  }
};