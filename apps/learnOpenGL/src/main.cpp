#include <glad/glad.h>

#include <vector>

#include "VBO.h"
#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include "VAO.h"


int main() {
  Window window { "LearnOpenGL" };
  window.init();

  Renderer renderer {};

  std::vector<float> vertices {
    0.5f,  -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
  };

  VBO vbo { vertices };
  VAO vao { 6 * sizeof(float) };
  vao.addAttrib<float>(3);
  vao.addAttrib<float>(3);

  Shader vert { "./assets/vert.glsl", GL_VERTEX_SHADER };
  Shader frag { "./assets/frag.glsl", GL_FRAGMENT_SHADER };
  Program program { vert, frag };
  program.bind();

  while (!window.isClosed()) {
    window.readInput();
    renderer.clear();

    vao.bind();
    program.bind();

    glDrawArrays(GL_TRIANGLES, 0, 3);

    window.processFrame();
  }
  return 0;
}