#pragma once

#include <vector>
class VBO {
public:
  VBO(const std::vector<float>);
private:
  unsigned int m_id;
};