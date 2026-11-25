#include "Scenes.h"

void Scene::clear_color() {
  glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
}

void Scene::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (const auto& sprite : sprites) {
    program.use();

    sprite->mesh.vao.bind();

    glDrawElements(GL_TRIANGLES, sprite->vertex_count, GL_UNSIGNED_INT, 0);
  }
}

void Scene::set_viewport(const Viewport& viewport) {
  glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
  this->viewport = viewport;
}

void Scene::set_polygon_mode(bool is_on) {
  glPolygonMode(GL_FRONT_AND_BACK, is_on ? GL_LINE : GL_FILL);
}