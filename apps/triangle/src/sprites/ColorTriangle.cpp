#include "sprites/ColorTriangle.h"

Vector3 colorStrToFloat(const std::string& hex) {
  return {
    std::stoi(hex.substr(0, 2), nullptr, 16) / 255.0f,
    std::stoi(hex.substr(2, 2), nullptr, 16) / 255.0f,
    std::stoi(hex.substr(4, 2), nullptr, 16) / 255.0f,
  };
}

ColorTriangle::ColorTriangle(Vector3 a, Vector3 b, Vector3 c)
  : a { a }, b { b }, c { c } {
  colorHex = "BADA55";
  shaderName = "colored";
}

std::vector<float> ColorTriangle::getCoords() const {
  auto color = colorStrToFloat(colorHex);
  return {
    a.x, a.y, a.z, color.x, color.y, color.z,
    b.x, b.y, b.z, color.x, color.y, color.z,
    c.x, c.y, c.z, color.x, color.y, color.z,
  };
}

std::vector<unsigned int> ColorTriangle::getIndices() const {
  return std::vector<unsigned int> { 0, 1, 2 };
}

int ColorTriangle::getVertexCount() const {
  return 3;
}

std::vector<VertexAttribute> ColorTriangle::getVAOLayout() const {
  return {
    { 3, GL_FLOAT },
    { 3, GL_FLOAT },
  };
}

void ColorTriangle::setColor(const std::string& hex) {
  colorHex = hex;
}