#include "sprites/Triangle.h"
#include "Graphics.h"

Triangle::Triangle(Vector3 a, Vector3 b, Vector3 c)
  : a { a }, b { b }, c { c } {}

std::vector<float> Triangle::getCoords() const {
  return {
    a.x, a.y, a.z,
    b.x, b.y, b.z,
    c.x, c.y, c.z
  };
}

std::vector<unsigned int> Triangle::getIndices() const {
  return std::vector<unsigned int> { 0, 1, 2 };
}

int Triangle::getVertexCount() const {
  return 3;
}

std::vector<VertexAttribute> Triangle::getVAOLayout() const {
  return {
    VertexAttribute { 3, GL_FLOAT }
  };
}