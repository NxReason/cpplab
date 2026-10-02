#include "Shader.h"
#include <iostream>

GLuint createShader(GLenum type, const char* source) {
  GLuint shader = glCreateShader(type);

  glShaderSource(shader, 1, &source, nullptr);
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

GLuint createShaderProgram() {
  const char* fragmentShader =
    R"(
    #version 330 core

    out vec4 FragColor;

    void main() {
      FragColor = vec4(0.2, 0.7, 1.0, 1.0);
    }
    )";
  const char* vertexShader =
    R"(
    #version 330 core

    layout(location = 0) in vec3 aPos;

    void main() {
      gl_Position = vec4(aPos, 1.0);
    }
    )";

  GLuint vertex = createShader(GL_VERTEX_SHADER, vertexShader);
  GLuint fragment = createShader(GL_FRAGMENT_SHADER, fragmentShader);

  GLuint program = glCreateProgram();

  glAttachShader(program, vertex);
  glAttachShader(program, fragment);

  glLinkProgram(program);

  glDeleteShader(vertex);
  glDeleteShader(fragment);

  return program;
}