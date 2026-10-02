#include "Renderer.h"

#include <glad/glad.h>

Renderer::Renderer() {
  float vertices[] = {
     0.0f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
  };

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  shader = createShaderProgram();
}

Renderer::~Renderer() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
}

void Renderer::setClearColor() {
  glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
}

void Renderer::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(shader);
  glad_glBindVertexArray(vao);

  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::setViewport(Viewport viewport) {
  glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
}