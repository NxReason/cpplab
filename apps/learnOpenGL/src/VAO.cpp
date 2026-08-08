#include "VAO.h"
#include <glad/glad.h>

VAO::VAO(unsigned int stride)
  : m_stride { stride }, m_index { 0 }, m_offset { 0 } {
  glGenVertexArrays(1, &m_id);
  glBindVertexArray(m_id);
}

template<>
void VAO::addAttrib<float>(unsigned int size) {
  glVertexAttribPointer(m_index, size, GL_FLOAT, GL_FALSE, m_stride, (void*)m_offset);
  glEnableVertexAttribArray(m_index);
  m_index++;
  m_offset += size * sizeof(float);
}

void VAO::bind() const {
  glBindVertexArray(m_id);
}

void VAO::unbind() const {
  glad_glBindVertexArray(0);
}

unsigned int VAO::getStride() const {
  return m_stride;
}

void VAO::setStride(unsigned int stride) {
  m_stride = stride;
}

unsigned int VAO::getId() const {
  return m_id;
}