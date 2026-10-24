#pragma once

#include <glad/glad.h>
#include <string>
#include <unordered_map>

#include "Vector.h"

class Shader {
public:
  Shader(int type, const char* filepath);

  unsigned int getId() const;
private:
  unsigned int id;
  int type;
};

class ShaderProgram {
public:
  ShaderProgram();
  ShaderProgram(Shader& vertex, Shader& fragment);
  ShaderProgram(const std::string& commonName);
  ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);

  void create(Shader& vertex, Shader& fragment);
  void use();

  void setUniforms(std::unordered_map<std::string, nxmath::Vector3> unis);
  void setUniform(const std::string& name, nxmath::Vector3 value);
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