#pragma once

#include <stbi_image.h>

#include <string>

class TextureImage {
public:
  int width;
  int height;
  int nChannels;
  unsigned char* data;

  TextureImage(const std::string& filepath = "", bool flip = true);
  void load(const std::string& filepath, bool flip = true);
  void free();

  bool isLoaded() const;
private:
  bool m_isLoaded;
};
