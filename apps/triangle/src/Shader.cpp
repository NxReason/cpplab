#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>


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