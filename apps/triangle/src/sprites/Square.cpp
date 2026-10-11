#include "sprites/Square.h"

Square::Square(Vector2 pos, float sideWidth)
  : pos { pos }, sideWidth { sideWidth } { }


std::vector<float> Square::getCoords() const {
  float offset = sideWidth / 2;
  return { 
    pos.x - offset, pos.y + offset, 0.0f,
    pos.x - offset, pos.y - offset, 0.0f,
    pos.x + offset, pos.y + offset, 0.0f,
    pos.x + offset, pos.y - offset, 0.0f,
  };
}

int Square::getVertexCount() const {
  return 4;
}