#pragma once

#include <vector>
#include "sprites/ISprite.h"

class TriangleScene {
public:
  TriangleScene();

  std::vector<ISprite*> getSprites() const;
private:
  std::vector<ISprite*> sprites;
};