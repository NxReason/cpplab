#include "Scene.h"
#include "sprites/Square.h"

SquareScene::SquareScene() {
  Square* s = new Square {
  };
  sprites.push_back(s);
}