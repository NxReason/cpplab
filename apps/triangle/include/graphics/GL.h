#pragma once

#include <vector>

class VBO {
public:
  VBO();
  void bind();
  void unbind();
  void data(const std::vector<float>& vertices);
  void data(const float* vertices, size_t size);
private:
  unsigned int id;
};

class EBO {
public:
  EBO();
  void bind();
  void data(const std::vector<unsigned int>& indices);
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
  void attrib_layout(const std::vector<VertexAttribute>& layout);
private:
  unsigned int id;
};