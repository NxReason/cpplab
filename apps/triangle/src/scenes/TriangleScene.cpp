#include "NxMath.h"
#include "Scenes.h"
#include "sprites/Square.h"
#include "sprites/Triangle.h"

TriangleScene::TriangleScene() {
  Triangle* t = new Triangle { 
    Vector2 { .x = -0.5, .y = -0.5 },
    Vector2 { .x =  0.5, .y = -0.5 },
    Vector2 { .x =  0.0, .y =  0.5 },
  };
  sprites.push_back(t);
}

std::vector<ISprite*> TriangleScene::getSprites() const {
  return sprites;
}