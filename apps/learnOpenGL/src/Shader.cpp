#include <fstream>
#include <iostream>
#include <glad/glad.h>
#include <sstream>
#include <string>
#include "Shader.h"

std::string getShaderName(int type) {
  switch (type) {
    case GL_VERTEX_SHADER:
      return "VERTEX";
    case GL_FRAGMENT_SHADER:
      return "FRAGMENT";
    default:
      return "UNKNOWN";
  }
}

Shader::Shader(const std::string& filepath, const int type) {
  std::string code;
  std::ifstream shaderFile;
  shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    shaderFile.open(filepath);
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();
    code = shaderStream.str();
  }
  catch (std::ifstream::failure e) {
    std::cout << "ERROR::SHADER::FILE_NOT_READ\n";
  }
  const char* source = code.c_str();
  m_id = glCreateShader(type);
  glShaderSource(m_id, 1, &source, nullptr);
  glCompileShader(m_id);

  int succcess;
  char infoLog[512];
  glGetShaderiv(m_id, GL_COMPILE_STATUS, &succcess);
  if (!succcess) {
    glGetShaderInfoLog(m_id, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::" << getShaderName(type) << "::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
}

void Shader::remove() {
  glDeleteShader(m_id);
}

unsigned int Shader::getId() const {
  return m_id;
}

Program::Program(const Shader& vert, const Shader& frag) {
  m_id = glCreateProgram();
  glAttachShader(m_id, vert.getId());
  glAttachShader(m_id, frag.getId());
  glLinkProgram(m_id);

  int success;
  char infoLog[512];
  glGetProgramiv(m_id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
    std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
}

void Program::bind() const {
  glUseProgram(m_id);
}

template<>
void Program::setUniform<bool>(const std::string& name, bool value) const {
  glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}
template<>
void Program::setUniform<int>(const std::string& name, int value) const {
  glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}
template<>
void Program::setUniform<float>(const std::string& name, float value) const {
  glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

unsigned int Program::getId() const {
  return m_id;
}