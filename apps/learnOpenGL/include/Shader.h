#pragma once

class Shader {
public:
  Shader(const int type);

  unsigned int getId() const;
  void remove();
private:
  unsigned int m_id;
};

class Program {
public:
  Program(const Shader& vert, const Shader& frag);

  void bind() const;
private:
  unsigned int m_id;
};