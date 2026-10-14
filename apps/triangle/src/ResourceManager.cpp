#include "ResourceManager.h"
#include "Graphics.h"
#include <vector>

int ResourceManager::id = 0;

Mesh ResourceManager::getMesh(int meshKey) {
  return meshMap[meshKey];
}

void ResourceManager::generateResources(IScene* scene) {
  for (auto& sprite : scene->getSprites()) {
    VBO vbo;
    VAO vao;

    vao.bind();
    vbo.bind();
    vbo.data(sprite->getCoords());

    auto attribs = std::vector<VertexAttribute>{ VertexAttribute { 3, GL_FLOAT } };
    vao.setAttributeLayout(attribs);

    sprite->meshName = id;
    meshMap[id++] = Mesh { vao, vbo };

    sprite->shaderName = "default";
  }
}