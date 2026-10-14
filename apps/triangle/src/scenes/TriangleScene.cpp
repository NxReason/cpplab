#include "NxMath.h"
#include "Scene.h"
#include "sprites/Triangle.h"

std::vector<ISprite*> IScene::getSprites() const {
  return sprites;
}

TriangleScene::TriangleScene() {
  Triangle* t = new Triangle { 
    Vector2 { .x = -0.5, .y = -0.5 },
    Vector2 { .x =  0.5, .y = -0.5 },
    Vector2 { .x =  0.0, .y =  0.5 },
  };
  sprites.push_back(t);
}
