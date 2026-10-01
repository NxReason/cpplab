#pragma once

#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>

// void framebuffer_size_callback(GLFWwindow*, int width, int height) {
//   glViewport(0, 0, width, height);
// }

class Window {
public:
  Window(int width, int height, const char* title = "") {
    if (!glfwInit()) {
      std::cerr << "Failed to initialize GLFW\n";
      created = false;
      return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(
      width,
      height,
      title,
      nullptr,
      nullptr
    );

    if (!window) {
      std::cerr << "Failed to create window\n";
      glfwTerminate();
      created = false;
      return;
    }

    glfwMakeContextCurrent(window);
    created = true;

    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int w, int h) {
      glViewport(0, 0, w, h);
    });

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cerr << "Failed to initialize GLAD\n";
      glfwDestroyWindow(window);
      glfwTerminate();
      created = false;
      return;
    }
  }

  GLFWwindow* getGlfwWindow() const {
    return window;
  }

  bool isCreated() const { return created; }
private:
  GLFWwindow* window;
  bool created;
};