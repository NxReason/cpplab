#pragma once

#include <glad/glad.h>
#include <string>

class Shader {
public:
  Shader(int type, const char* filepath);
  unsigned int create();
private:
  int type;
  std::string source;
};

class ShaderProgram {
public:
  ShaderProgram();
  ShaderProgram(Shader& vertex, Shader& fragment);

  void create(Shader& vertex, Shader& fragment);
  void use();
private:
  unsigned int id;
};