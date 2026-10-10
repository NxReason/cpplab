#pragma once

#include <glad/glad.h>
#include <vector>

class VBO {
public:
  VBO();
  void bind();
  void data(std::vector<float> vertices);
  void data(const float* vertices, size_t size);
private:
  unsigned int id;
};

struct VertexAttribute {
  int size;
  int type;
};

class VAO {
public:
  VAO();
  void bind();
  void setAttributeLayout(const std::vector<VertexAttribute>& layout);
private:
  unsigned int id;
};