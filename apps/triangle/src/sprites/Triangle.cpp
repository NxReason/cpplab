#include "sprites/Triangle.h"
#include "Graphics.h"

Triangle::Triangle() {
  // a
  coords.push_back(-0.5);
  coords.push_back(0.5);
  coords.push_back(0.0);
  // b
  coords.push_back(0.0);
  coords.push_back(-0.5);
  coords.push_back(0.0);
  // c
  coords.push_back(0.5);
  coords.push_back(0.5);
  coords.push_back(0.0);
}

Triangle::Triangle(Vector2 a, Vector2 b, Vector2 c) {
  // a
  coords.push_back(a.x);
  coords.push_back(a.y);
  coords.push_back(0.0);
  // b
  coords.push_back(b.x);
  coords.push_back(b.y);
  coords.push_back(0.0);
  // c
  coords.push_back(c.x);
  coords.push_back(c.y);
  coords.push_back(0.0);
}

std::vector<float> Triangle::getCoords() const {
  return coords;
}

std::vector<VertexAttribute> Triangle::getAttributeLayout() const {
  std::vector<VertexAttribute> layout { VertexAttribute { .size = 3, .type = GL_FLOAT} };
  return layout;
}