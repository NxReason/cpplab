#include "Scene.h"
#include "sprites/ColorTriangle.h"

ColoredTriangle::ColoredTriangle() {
  auto* tColor = new ColorTriangle {
    { -0.9, 0.9 },
    { -0.9, 0.0 },
    { 0.0, 0.9 },
  };
  tColor->setColor("00ff00");

  auto* tColorUni = new ColorTriangleUni {
    { 0.9, -0.9 },
    { 0.9, 0.0 },
    { 0.0, -0.9 },
  };
  tColorUni->setColor("ff0000");

  sprites.push_back(tColor);
  sprites.push_back(tColorUni);
}
