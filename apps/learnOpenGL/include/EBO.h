#pragma once

#include <vector>
class EBO {
public:
  EBO(const std::vector<unsigned int>);
  void bind() const;
private:
  unsigned int m_id;
};