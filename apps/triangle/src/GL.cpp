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

void VBO::data(std::vector<float> vertices) {
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

void VBO::data(const float* vertices, size_t size) {
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Index Buffer


// Vertex Attributes

VAO::VAO() {
  glGenVertexArrays(1, &id);
}

void VAO::bind() {
  glBindVertexArray(id);
}

void VAO::attrib_layout() {
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
}