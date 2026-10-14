#include "sprites/Square.h"

Square::Square(Vector3 pos, float sideWidth)
  : pos { pos }, sideWidth { sideWidth } { }


std::vector<float> Square::getCoords() const {
  float offset = sideWidth / 2;
  // return { 
  //   // triangle 1
  //   pos.x - offset, pos.y - offset, 0.0f,
  //   pos.x - offset, pos.y + offset, 0.0f,
  //   pos.x + offset, pos.y - offset, 0.0f,
  //   // triangle 2
  //   pos.x + offset, pos.y + offset, 0.0f,
  //   pos.x - offset, pos.y + offset, 0.0f,
  //   pos.x + offset, pos.y - offset, 0.0f,
  // };
  return {
    pos.x - offset, pos.y - offset, 0.0f,
    pos.x - offset, pos.y + offset, 0.0f,
    pos.x + offset, pos.y + offset, 0.0f,
    pos.x + offset, pos.y - offset, 0.0f,
  };
}

std::vector<unsigned int> Square::getIndices() const {
  return std::vector<unsigned int> { 0, 1, 3, 1, 2, 3 };
}

int Square::getVertexCount() const {
  return 6;
}

std::vector<VertexAttribute> Square::getVAOLayout() const {
  return {
    VertexAttribute { 3, GL_FLOAT }
  };
}