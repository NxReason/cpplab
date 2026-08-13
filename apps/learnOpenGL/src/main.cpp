#include <glad/glad.h>

#include <vector>

#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Data.h"
#include "glm/trigonometric.hpp"

#include <stbi_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {
  int width { 800 }, height { 600 };
  Window window { width, height, "LearnOpenGL" };
  window.init();

  Renderer renderer {};

  // std::vector<float> vertices {
  //   0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
  //   0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
  //   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
  //   -0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
  // };
  // std::vector<unsigned int> indices = {
  //   0, 1, 3,
  //   1, 2, 3
  // };
  // std::vector<float> vertices {
  //   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
  //    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
  //    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  //    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  //   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
  //   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
  // };
  VBO vbo { vertices, 180 };
  // EBO ebo { indices };
  VAO vao { 5 * sizeof(float) };
  vbo.bind();
  // ebo.bind();
  vao.addAttrib<float>(3);
  // vao.addAttrib<float>(3);
  vao.addAttrib<float>(2);

  // textures
  Texture t1 { 0 };
  Texture t2 { 1 };
  TextureImage ti1 { "./assets/container.jpg" };
  TextureImage ti2 { "./assets/awesomeface.png" };

  t1.loadImage(ti1);
  t2.loadImage(ti2);

  Shader vert { "./shaders/transform.vert", GL_VERTEX_SHADER };
  Shader frag { "./shaders/texture.frag", GL_FRAGMENT_SHADER };
  Program program { vert, frag };
  program.bind();
  program.setUniform<int>("texture1", 0);
  program.setUniform<int>("texture2", 1);

  glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)
  };

  glm::mat4 view = glm::mat4{ 1.0f };
  view = glm::translate(view, glm::vec3{ 0.0f, 0.0f, -3.0f });
  glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width/(float)(height), 0.1f, 100.0f);

  renderer.depthTest();

  while (!window.isClosed()) {
    window.readInput();
    renderer.clear();

    t1.bind();
    t2.bind();
    vao.bind();
    program.bind();

    // transform
    // glm::mat4 model = glm::mat4{ 1.0f };
    // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3{0.5f, 1.0f, 0.0f });
    // program.setUniform<glm::mat4>("model", model);
    program.setUniform<glm::mat4>("view", view);
    program.setUniform<glm::mat4>("proj", proj);

    for (unsigned int i = 0; i < 10; i++) {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * (i + 1) * (float)glfwGetTime();
      model = glm::rotate(model, glm::radians(angle), glm::vec3{ 1.0f, 0.3f, 0.5f });
      program.setUniform("model", model);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    window.processFrame();
  }
  return 0;
}