#include "ResourceManager.h"
#include "Graphics.h"

int ResourceManager::id = 0;

Mesh ResourceManager::getMesh(int meshKey) {
  return meshMap[meshKey];
}

void ResourceManager::generateResources(IScene* scene) {
  for (auto& sprite : scene->getSprites()) {
    VBO vbo;
    EBO ebo;
    VAO vao;

    vao.bind();
    vbo.bind();
    ebo.bind();
    vbo.data(sprite->getCoords());
    ebo.data(sprite->getIndices());

    vao.setAttributeLayout(sprite->getVAOLayout());

    sprite->meshName = id;
    meshMap[id++] = Mesh { vao, vbo, ebo };
  }
}