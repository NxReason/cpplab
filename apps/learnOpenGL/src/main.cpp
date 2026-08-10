#include <glad/glad.h>

#include <vector>

#include "VBO.h"
#include "EBO.h"
#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include "VAO.h"

#include <stbi_image.h>

struct Texture {
  unsigned int id;
  int slot;
};
Texture addTexture(const char* filename, int slot) {
  unsigned int texture;
  glGenTextures(1, &texture);
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

  auto format = nrChannels == 3 ? GL_RGB : GL_RGBA;
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  stbi_image_free(data);
  return Texture { texture, slot };
}

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
  auto t1 = addTexture("./assets/container.jpg", 0);
  auto t2 = addTexture("./assets/awesomeface.png", 1);

  Shader vert { "./shaders/texture.vert", GL_VERTEX_SHADER };
  Shader frag { "./shaders/texture.frag", GL_FRAGMENT_SHADER };
  Program program { vert, frag };
  program.bind();
  program.setUniform<int>("texture1", 0);
  program.setUniform<int>("texture2", 1);

  while (!window.isClosed()) {
    window.readInput();
    renderer.clear();

    // glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(t1.slot);
    glBindTexture(GL_TEXTURE_2D, t1.id);
    glActiveTexture(t2.slot);
    glBindTexture(GL_TEXTURE_2D, t2.id);
    vao.bind();
    program.bind();

    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    window.processFrame();
  }
  return 0;
}