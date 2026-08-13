#include "VBO.h"
#include <glad/glad.h>
#include <vector>

VBO::VBO(const std::vector<float> vertices) {
  glGenBuffers(1, &m_id);
  glBindBuffer(GL_ARRAY_BUFFER, m_id);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

VBO::VBO(const float* vertices, int count) {
  glGenBuffers(1, &m_id);
  glBindBuffer(GL_ARRAY_BUFFER, m_id);
  glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
}

void VBO::bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, m_id);
}