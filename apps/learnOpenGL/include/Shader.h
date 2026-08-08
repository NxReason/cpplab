#pragma once

#include <string>
class Shader {
public:
  Shader(const std::string& filepath, const int type);

  unsigned int getId() const;
  void remove();
private:
  unsigned int m_id;
};

class Program {
public:
  Program(const Shader& vert, const Shader& frag);

  void bind() const;

  template<typename T>
  void setUniform(const std::string& name, T value) const;

  unsigned int getId() const;
private:
  unsigned int m_id;
};