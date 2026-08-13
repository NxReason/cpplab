#include <glad/glad.h>

#include <vector>

#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"

#include <stbi_image.h>

int main() {
  Window window { "LearnOpenGL" };
  window.init();

  Renderer renderer {};

  // std::vector<float> vertices {
  //   0.5f,  -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 
  //   -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
  //   0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
  // };

  // VBO vbo { vertices };
  // VAO vao { 6 * sizeof(float) };
  // vao.addAttrib<float>(3);
  // vao.addAttrib<float>(3);
  std::vector<float> vertices {
    0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
  };
  std::vector<unsigned int> indices = {
    0, 1, 3,
    1, 2, 3
  };
  VBO vbo { vertices };
  EBO ebo { indices };
  VAO vao { 8 * sizeof(float) };
  vbo.bind();
  ebo.bind();
  vao.addAttrib<float>(3);
  vao.addAttrib<float>(3);
  vao.addAttrib<float>(2);

  // textures
  Texture t1 { 0 };
  Texture t2 { 1 };
  TextureImage ti1 { "./assets/container.jpg" };
  TextureImage ti2 { "./assets/awesomeface.png" };

  t1.loadImage(ti1);
  t2.loadImage(ti2);

  Shader vert { "./shaders/texture.vert", GL_VERTEX_SHADER };
  Shader frag { "./shaders/texture.frag", GL_FRAGMENT_SHADER };
  Program program { vert, frag };
  program.bind();
  program.setUniform<int>("texture1", 0);
  program.setUniform<int>("texture2", 1);

  while (!window.isClosed()) {
    window.readInput();
    renderer.clear();

    t1.bind();
    t2.bind();
    vao.bind();
    program.bind();

    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    window.processFrame();
  }
  return 0;
}