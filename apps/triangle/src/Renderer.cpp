#include "Renderer.h"
#include "Scenes.h"
#include "sprites/Triangle.h"

#include <glad/glad.h>

Renderer::Renderer() {
  // Triangle triangle;
  // auto coords = triangle.getCoords();
  // auto layout = triangle.getAttributeLayout();

  // vao.bind();

  // vbo.bind();
  // vbo.data(coords);

  // vao.setAttributeLayout(layout);

  Shader vert { GL_VERTEX_SHADER, "./shaders/default.vert" };
  Shader frag { GL_FRAGMENT_SHADER, "./shaders/default.frag" };
  program.create(vert, frag);
}

Renderer::~Renderer() {
  // glDeleteVertexArrays(1, &vao);
  // glDeleteBuffers(1, &vbo);
}

void Renderer::setClearColor() {
  glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
}

void Renderer::render() {
  // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // program.use();
  // vao.bind();

  // glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::render(TriangleScene) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  program.use();
  for (auto vao : vaos) {
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }
}

void Renderer::genBuffers(TriangleScene scene) {
  auto triangles = scene.getTriangles();
  for (auto triangle : triangles) {
    auto coords = triangle.getCoords();
    auto layout = triangle.getAttributeLayout();
    VAO vao;
    VBO vbo;

    vao.bind();

    vbo.bind();
    vbo.data(coords);

    vao.setAttributeLayout(layout);
    vbos.push_back(vbo);
    vaos.push_back(vao);
  }
}

void Renderer::setViewport(Viewport viewport) {
  glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
}
