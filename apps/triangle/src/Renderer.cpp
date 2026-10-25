#include "graphics/Renderer.h"
#include "graphics/GL.h"
#include "graphics/Shader.h"

#include <glad/glad.h>

Renderer::Renderer() { }

Renderer::~Renderer() {
  // glDeleteVertexArrays(1, &vao);
  // glDeleteBuffers(1, &vbo);
}

void Renderer::clear_color() {
  glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
}


void Renderer::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  program.use();
  vao.bind();
  glDrawArrays(GL_TRIANGLES, 0, 3);
  // for (auto& sprite : sprites) {
  //   ShaderProgram program = shaderManager.getShader(sprite->shaderName);
  //   program.use();
  //   program.setUniforms(sprite->uniforms);

  //   Mesh mesh = resourceManager.getMesh(sprite->meshId);
  //   mesh.vao.bind();

  //   // glDrawArrays(GL_TRIANGLES, 0, sprite->getVertexCount());
  //   glDrawElements(GL_TRIANGLES, sprite->getVertexCount(), GL_UNSIGNED_INT, 0);
  // }
}

void Renderer::gen_resources() {
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
  };
  vao.bind();
  VBO vbo;
  vbo.bind();
  vbo.data(vertices, sizeof(vertices));
  vao.attrib_layout();

  program.create("default");
}


void Renderer::set_viewport(const Viewport& viewport) {
  glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
}

void Renderer::set_polygon_mode(bool isOn) {
  glPolygonMode(GL_FRONT_AND_BACK, isOn ? GL_LINE : GL_FILL);
}
