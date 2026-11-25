#pragma once

#include <vector>
#include <glad/glad.h>

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
  int stride;
};

class VAO {
public:
  VAO();
  void bind();
  void attrib_layout(const std::vector<VertexAttribute>& layout);

  template<typename T>
  void enable_attribute(int index = 0, long long offset = 0, int stride = 3 * sizeof(float));

  unsigned int get_id() const { return id; }
private:
  unsigned int id;
};
