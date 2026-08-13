#include "TextureImage.h"

TextureImage::TextureImage(const std::string& filepath, bool flip) {
  if (filepath == "") {
    m_isLoaded = false;
    return;
  }
  stbi_set_flip_vertically_on_load(flip);
  data = stbi_load(filepath.c_str(), &width, &height, &nChannels, 0);
  m_isLoaded = true;
}

void TextureImage::load(const std::string& filepath, bool flip) {
  if (m_isLoaded) {
    free();
  }
  stbi_set_flip_vertically_on_load(flip);
  data = stbi_load(filepath.c_str(), &width, &height, &nChannels, 0);
  m_isLoaded = true;
}

void TextureImage::free() {
  stbi_image_free(data);
  m_isLoaded = false;
}

bool TextureImage::isLoaded() const {
  return m_isLoaded;
}