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

  std::stringstream buffer;
  buffer << file.rdbuf();

  source = buffer.str();
  file.close();
}

unsigned int Shader::create() {
  GLuint shader = glCreateShader(type);

  auto shader_str = source.c_str();
  glShaderSource(shader, 1, &shader_str, nullptr);
  glCompileShader(shader);

  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char info[512];
    glGetShaderInfoLog(shader, 512, nullptr, info);
    std::cerr << info << '\n';
  }
  return shader;
}

// PROGRAM
ShaderProgram::ShaderProgram() {
  id = glCreateProgram();
}

ShaderProgram::ShaderProgram(Shader& vertex, Shader& fragment) {
  id = glCreateProgram();

  create(vertex, fragment);
}

void ShaderProgram::create(Shader& vertex, Shader& fragment) {
  auto vertexId = vertex.create();
  auto fragmentId = fragment.create();

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
  auto vertShader = Shader(GL_VERTEX_SHADER, "./shaders/default.vert");
  auto fragShader = Shader(GL_FRAGMENT_SHADER, "./shaders/default.frag");
  auto program = ShaderProgram(vertShader, fragShader);
  shaders["default"] = program;

  auto coloredVert = Shader(GL_VERTEX_SHADER, "./shaders/colored.vert");
  auto coloredFrag = Shader(GL_FRAGMENT_SHADER, "./shaders/colored.frag");
  auto coloredProgram = ShaderProgram(coloredVert, coloredFrag);
  shaders["colored"] = coloredProgram;

  auto coloredUniVert = Shader(GL_VERTEX_SHADER, "./shaders/colored_uni.vert");
  auto coloredUniFrag = Shader(GL_FRAGMENT_SHADER, "./shaders/colored_uni.frag");
  auto coloredUniProgram = ShaderProgram(coloredUniVert, coloredUniFrag);
  shaders["colored_uni"] = coloredUniProgram;
}

ShaderProgram ShaderManager::getShader(const std::string& shaderName) const {
  if(shaders.contains(shaderName)) {
    return shaders.at(shaderName);
  }
  return shaders.at("default");
}