#include <iostream>
#include <glad/glad.h>
#include <string>
#include "Shader.h"

const char* vertexShader = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main() {
  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

const char* fragmentShader = R"(
#version 330 core
out vec4 FragColor;

void main() {
  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

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

Shader::Shader(const int type) {
  m_id = glCreateShader(type);
  const char* source = type == GL_VERTEX_SHADER ? vertexShader : fragmentShader;
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