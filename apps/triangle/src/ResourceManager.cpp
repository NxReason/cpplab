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
    EBO ebo;
    VAO vao;

    vao.bind();
    vbo.bind();
    ebo.bind();
    vbo.data(sprite->getCoords());
    ebo.data(sprite->getIndices());

    auto attribs = std::vector<VertexAttribute>{ VertexAttribute { 3, GL_FLOAT } };
    vao.setAttributeLayout(attribs);

    sprite->meshName = id;
    meshMap[id++] = Mesh { vao, vbo, ebo };

    sprite->shaderName = "default";
  }
}