#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>


Shader::Shader(int type, const char* filepath)
  : type { type } {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open shader");
  }

  // read file content
  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();

  // create shader
  auto source_str = buffer.str();
  auto source = source_str.c_str();
  id = glCreateShader(type);

  glShaderSource(id, 1, &source, nullptr);
  glCompileShader(id);

  int success;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (!success) {
    char info[512];
    glGetShaderInfoLog(id, 512, nullptr, info);
    std::cerr << info << '\n';
  }
}


unsigned int Shader::getId() const {
  return id;
}

// PROGRAM
ShaderProgram::ShaderProgram() {
  id = glCreateProgram();
}

ShaderProgram::ShaderProgram(Shader& vertex, Shader& fragment) {
  id = glCreateProgram();
  create(vertex, fragment);
}

ShaderProgram::ShaderProgram(const std::string& commonName) 
  : ShaderProgram { 
    "./shaders/" + commonName + ".vert",
    "./shaders/" + commonName + ".frag"
  } {}

ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) {
  auto vertex = Shader(GL_VERTEX_SHADER, vertexPath.c_str());
  auto fragment = Shader(GL_FRAGMENT_SHADER, fragmentPath.c_str());

  id = glCreateProgram();
  create(vertex, fragment);
}

void ShaderProgram::create(Shader& vertex, Shader& fragment) {
  auto vertexId = vertex.getId();
  auto fragmentId = fragment.getId();

  glAttachShader(id, vertexId);
  glAttachShader(id, fragmentId);

  glLinkProgram(id);

  glDeleteShader(vertexId);
  glDeleteShader(fragmentId);
}

void ShaderProgram::use() {
  glUseProgram(id);
}

void ShaderProgram::setUniforms(std::unordered_map<std::string, nxmath::Vector3> unis) {
  for (const auto& uniform : unis) {
    setUniform(uniform.first, uniform.second);
  }
}

void ShaderProgram::setUniform(const std::string& name, const nxmath::Vector3 val) {
  int location = glGetUniformLocation(id, name.c_str());
  glUniform3f(location, val.x, val.y, val.z);
}

// MANAGER
ShaderManager::ShaderManager() {
  shaders["default"] = ShaderProgram { "default" };
  shaders["colored"] = ShaderProgram { "colored" };
  shaders["colored_uni"] = ShaderProgram { "colored_uni" };
}

ShaderProgram ShaderManager::getShader(const std::string& shaderName) const {
  if(shaders.contains(shaderName)) {
    return shaders.at(shaderName);
  }
  return shaders.at("default");
}