#pragma once

#include <string>
#include <unordered_map>

#include <glad/glad.h>

#include "Vector.h"

class Shader {
public:
  Shader(int type, const char* filepath);
  Shader(int type, const std::string& filepath);

  unsigned int getId() const;
private:
  unsigned int id;
  int type;
};

class ShaderProgram {
public:
  ShaderProgram();
  ShaderProgram(Shader& vertex, Shader& fragment);
  ShaderProgram(const std::string& common_name);
  ShaderProgram(const std::string& vertex_path, const std::string& fragment_path);

  void create(const std::string& common_name);
  void create(Shader& vertex, Shader& fragment);
  void use();

  void setUniforms(std::unordered_map<std::string, nxmath::Vector3> unis);
  void setUniform(const std::string& name, nxmath::Vector3 value);
private:
  unsigned int id;
};