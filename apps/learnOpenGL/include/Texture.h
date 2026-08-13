#pragma once
#include <glad/glad.h>
#include "TextureImage.h"

class Texture {
public:
  Texture(unsigned int slot = 0);

  void bind() const;
  void loadImage(const TextureImage& tid);

  unsigned int getSlot() const;
  void setSlot(unsigned int slot);
private:
  unsigned int m_id;
  unsigned int m_slot;
};
