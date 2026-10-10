#include "Graphics.h"

VBO::VBO() {
  glGenBuffers(1, &id);
}

void VBO::bind() {
  glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::data(std::vector<float> vertices) {
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

void VBO::data(const float* vertices, size_t size) {
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}