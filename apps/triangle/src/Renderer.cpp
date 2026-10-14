#include "Renderer.h"

#include <glad/glad.h>

Renderer::Renderer() { }

Renderer::~Renderer() {
  // glDeleteVertexArrays(1, &vao);
  // glDeleteBuffers(1, &vbo);
}

void Renderer::setClearColor() {
  glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
}


void Renderer::render(IScene* scene) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  auto sprites = scene->getSprites();
  for (auto& sprite : sprites) {
    ShaderProgram program = shaderManager.getShader(sprite->shaderName);
    program.use();
    program.setUniforms(sprite->uniforms);

    Mesh mesh = resourceManager.getMesh(sprite->meshName);
    mesh.vao.bind();

    // glDrawArrays(GL_TRIANGLES, 0, sprite->getVertexCount());
    glDrawElements(GL_TRIANGLES, sprite->getVertexCount(), GL_UNSIGNED_INT, 0);
  }
}

void Renderer::generateResources(IScene* scene) {
  resourceManager.generateResources(scene);
}


void Renderer::setViewport(const Viewport& viewport) {
  glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
}

void Renderer::setPolygonMode(bool isOn) {
  glPolygonMode(GL_FRONT_AND_BACK, isOn ? GL_LINE : GL_FILL);
}
