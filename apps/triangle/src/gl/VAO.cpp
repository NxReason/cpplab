#include "Graphics.h"


VAO::VAO() {
  glGenVertexArrays(1, &id);
}

void VAO::bind() {
  glBindVertexArray(id);
}

void VAO::setAttributeLayout(const std::vector<VertexAttribute>& layout) {
  int stride = 0;
  for (const auto& attrib : layout) {
    // TODO: change 4 to actual type size
    stride += attrib.size * 4;
  }

  int index = 0;
  long long pad = 0;
  for (const auto& attrib : layout) {
    glVertexAttribPointer(index, attrib.size, attrib.type, GL_FALSE, stride, (void*)pad);
    glEnableVertexAttribArray(index);
    index++;
    // TODO: change float to actual type
    pad += attrib.size * sizeof(float);
  }
}
