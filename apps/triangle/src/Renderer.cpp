#include "Renderer.h"
#include "Scenes.h"

#include <glad/glad.h>

Renderer::Renderer() { }

Renderer::~Renderer() {
  // glDeleteVertexArrays(1, &vao);
  // glDeleteBuffers(1, &vbo);
}

void Renderer::setClearColor() {
  glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
}


void Renderer::render(TriangleScene scene) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  auto sprites = scene.getSprites();
  for (auto& sprite : sprites) {
    ShaderProgram program = shaderManager.getShader(sprite->shaderName);
    program.use();

    Mesh mesh = resourceManager.getMesh(sprite->meshName);
    mesh.vao.bind();

    glDrawArrays(GL_TRIANGLES, 0, sprite->getVertexCount());
  }
}

void Renderer::generateResources(TriangleScene scene) {
  resourceManager.generateResources(scene);
}


void Renderer::setViewport(Viewport viewport) {
  glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
}
