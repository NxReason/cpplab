#include "Texture.h"
#include <glad/glad.h>

Texture::Texture(unsigned int slot)
  : m_slot { slot } {
  glGenTextures(1, &m_id);
  glActiveTexture(GL_TEXTURE0 + m_slot);
  glBindTexture(GL_TEXTURE_2D, m_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::bind() const {
  glActiveTexture(m_slot);
  glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::loadImage(const TextureImage& tid) {
  bind();
  auto format = tid.nChannels == 3 ? GL_RGB : GL_RGBA;
  if (tid.data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tid.width, tid.height, 0, format, GL_UNSIGNED_BYTE, tid.data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
}

unsigned int Texture::getSlot() const {
  return m_slot;
}
void Texture::setSlot(unsigned int slot) {
  m_slot = slot;
}