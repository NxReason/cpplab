#include "ResourceManager.h"

int ResourceManager::id = 0;

Mesh ResourceManager::getMesh(int meshKey) {
  return meshMap[meshKey];
}

void ResourceManager::generateResources(TriangleScene scene) {
  for (auto& sprite : scene.getSprites()) {
    VBO vbo;
    VAO vao;

    vao.bind();
    vbo.bind();
    vbo.data(sprite->getCoords());

    sprite->meshName = id;
    meshMap[id++] = Mesh { vao, vbo };

    sprite->shaderName = "default";
  }
}