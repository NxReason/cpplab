#include <glad/glad.h>
#include "Window.h"
#include "Renderer.h"
#include "Shader.h"

int main() {
  Window window { "LearnOpenGL" };
  window.init();

  Renderer renderer {};

  float vertices[] = {
    0.5f,  0.5f, 0.0f,
    0.5f,  -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f
  };
  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  unsigned int EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  Shader vert { GL_VERTEX_SHADER };
  Shader frag { GL_FRAGMENT_SHADER };
  Program program { vert, frag };

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  program.bind();

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!window.isClosed()) {
    window.readInput();
    renderer.clear();

    program.bind();
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    window.processFrame();
  }
  return 0;
}