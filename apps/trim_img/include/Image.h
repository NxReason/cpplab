#pragma once

#include <iostream>
#include <ostream>
#include <string>
#include <filesystem>

#include "stb_image.h"
#include "stb_image_write.h"

namespace fs = std::filesystem;

std::string operator+(const std::string& str, const fs::path& path);
std::string operator+(const fs::path& path, const std::string& str);

struct Rect {
  int x, y;
  int width, height;
};

std::ostream& operator<<(std::ostream& out, const Rect& rect);

struct Color {
  unsigned char r, g, b, a;
};

class Image {
public:
  int width, height, channels;
  unsigned char* pixels { nullptr };
  Rect opaque;
  fs::path path;

  Image(fs::path path);

  void calc_opaque_rect();

  void write();

  Color get_pixel_at(int row, int col);

  void describe() const;

  void free();
};