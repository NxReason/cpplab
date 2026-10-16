#include "Image.h"

#include <stdexcept>

std::ostream& operator<<(std::ostream& out, const Rect& rect) {
  out << "x: " << rect.x << ", y: " << rect.y << ", width: " << rect.width << ", height: " << rect.height;
  return out;
}

std::string operator+(const fs::path& path, const std::string& str) {
  return path.string() + str;
}

std::string operator+(const std::string& str, const fs::path& path) {
  return str + path.string();
}

Image::Image(fs::path path)
: path { path } {
  pixels = stbi_load(
    path.string().c_str(),
    &width, &height, &channels, 4
  );

  if (!pixels) {
    throw std::invalid_argument("Failed to load image");
  }
}

void Image::calc_opaque_rect() {
  int firstRow = height, firstCol = width;
  int lastRow = -1, lastCol = -1;
  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      auto pixel = get_pixel_at(row, col);
      if (pixel.a == 0.0) continue;

      if (row < firstRow) firstRow = row;
      if (col < firstCol) firstCol = col;
      if (row > lastRow) lastRow = row;
      if (col > lastCol) lastCol = col;
    }
  }
  opaque = { firstCol, firstRow, lastCol - firstCol + 1, lastRow - firstRow + 1 };
}
void Image::write() {
  auto buffer = new unsigned char[opaque.width * opaque.height * 4];

  for (int row = 0; row < opaque.height; ++row) {
    for (int col = 0; col < opaque.width; ++col) {
      Color source_pixel = get_pixel_at(row + opaque.y, col + opaque.x);
      int buff_i = (row * opaque.width + col) * 4;
      buffer[buff_i] = source_pixel.r;
      buffer[buff_i + 1] = source_pixel.g;
      buffer[buff_i + 2] = source_pixel.b;
      buffer[buff_i + 3] = source_pixel.a;
    }
  }

  auto out_name = path.stem() + "_opaque" + path.extension();
  auto out_path = path.parent_path() + "/" + out_name;

  stbi_write_png(
    out_path.c_str(),
    opaque.width,
    opaque.height,
    4,
    buffer,
    opaque.width * 4
  );

  delete[] buffer;
}

Color Image::get_pixel_at(int row, int col) {
  int i = (row * width + col) * 4;
  return Color { pixels[i], pixels[i + 1], pixels[i + 2], pixels[i + 3] };
}

void Image::describe() const {
  std::cout << path.filename() << '\n';
  std::cout << "Source [" << width << " x " << height << "]\n";
  std::cout << "Opaque [" << opaque << "]" << '\n';
}

void Image::free() {
  if (pixels) {
    stbi_image_free(pixels);
  }
}