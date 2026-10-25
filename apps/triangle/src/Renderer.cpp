#include "graphics/Renderer.h"
#include "ResourceManager.h"
#include "graphics/Shader.h"

#include <glad/glad.h>

Renderer::Renderer() {
  program.create("default");
}

Renderer::~Renderer() { }

void Renderer::clear_color() {
  glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
}


void Renderer::render(ResourceManager& res_manager, const Scene* scene) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // program.use();
  // vao.bind();
  // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

  for (const auto& sprite : scene->sprites) {
  //   ShaderProgram program = shaderManager.getShader(sprite->shaderName);
    program.use();
  //   program.setUniforms(sprite->uniforms);

    Mesh mesh = res_manager.get_mesh(sprite->mesh_id);
    mesh.vao.bind();

    glDrawElements(GL_TRIANGLES, sprite->vertex_count, GL_UNSIGNED_INT, 0);
  }
}

// void Renderer::gen_resources(const Scene& scene) {
//   for (const auto& sprite : scene.sprites) {
//   }
  // float vertices[] = {
  //   -0.5f, -0.5f, 0.0f,
  //   0.5f, -0.5f, 0.0f,
  //   0.0f, 0.5f, 0.0f,
  // };
  // vao.bind();
  // VBO vbo;
  // vbo.bind();
  // vbo.data(vertices, sizeof(vertices));
  // std::vector<unsigned int> indices = { 0, 1, 2 };
  // EBO ebo;
  // ebo.bind();
  // ebo.data(indices);
  // vao.attrib_layout();

//   program.create("default");
// }


void Renderer::set_viewport(const Viewport& viewport) {
  glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
}

void Renderer::set_polygon_mode(bool isOn) {
  glPolygonMode(GL_FRONT_AND_BACK, isOn ? GL_LINE : GL_FILL);
}
