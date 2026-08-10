#include "EBO.h"
#include <glad/glad.h>
#include <vector>

EBO::EBO(const std::vector<unsigned int> indices) {
  glGenBuffers(1, &m_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void EBO::bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}