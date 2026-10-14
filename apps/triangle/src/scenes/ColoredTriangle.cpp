#include "Scene.h"
#include "sprites/ColorTriangle.h"

ColoredTriangle::ColoredTriangle() {
  auto* t = new ColorTriangle;

  t->setColor("00ff00");

  sprites.push_back(t);
}
