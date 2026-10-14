#include "Graphics.h"


EBO::EBO() {
  glGenBuffers(1, &id);
}

void EBO::bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void EBO::data(std::vector<unsigned int> indices) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}