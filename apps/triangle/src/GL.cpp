#include "graphics/GL.h"
#include "app/Window.h"


// Vertex Buffer
VBO::VBO() {
  glGenBuffers(1, &id);
}

void VBO::bind() {
  glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::data(const std::vector<float>& vertices) {
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

void VBO::data(const float* vertices, size_t size) {
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}


// Index Buffer
EBO::EBO() {
  glGenBuffers(1, &id);
}

void EBO::bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void EBO::data(const std::vector<unsigned int>& indices) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}


// Vertex Attributes
VAO::VAO() {
  glGenVertexArrays(1, &id);
}

void VAO::bind() {
  glBindVertexArray(id);
}

void VAO::attrib_layout(const std::vector<VertexAttribute>& layout) {
  int stride = layout.size() * 3;
  int index = 0;
  long long offset = 0;
  for (const auto& attrib : layout) {
    glVertexAttribPointer(index, attrib.size, attrib.type, GL_FALSE, stride, (void*)offset);
    glEnableVertexAttribArray(index++);
    offset += attrib.size * sizeof(float);
  }
}