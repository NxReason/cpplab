#include "ResourceManager.h"

int ResourceManager::id = 0;

Mesh ResourceManager::get_mesh(int mesh_key) {
  return mesh_map[mesh_key];
}

void ResourceManager::gen_resources(const Scene* scene) {
  for (const auto& sprite : scene->sprites) {
    VBO vbo;
    EBO ebo;
    VAO vao;

    vao.bind();
    vbo.bind();
    ebo.bind();
    vbo.data(sprite->get_coords());
    ebo.data(sprite->get_indices());

    vao.attrib_layout(sprite->vao_layout());

    sprite->mesh_id = id;
    mesh_map[id++] = Mesh { vao, vbo, ebo };
  }
}