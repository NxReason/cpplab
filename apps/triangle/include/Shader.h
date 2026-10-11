#pragma once

#include <glad/glad.h>
#include <string>
#include <unordered_map>

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

class ShaderManager {
private:
  std::unordered_map<std::string, ShaderProgram> shaders;

public:
  ShaderManager();
  ShaderProgram getShader(const std::string& shaderName) const;
};