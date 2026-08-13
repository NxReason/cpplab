#pragma once

#include <vector>
class VBO {
public:
  VBO(const std::vector<float>);
  VBO(const float* vertices, int count);
  void bind() const;
private:
  unsigned int m_id;
};