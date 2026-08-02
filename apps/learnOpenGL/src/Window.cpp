#include "Window.h"

#include <GLFW/glfw3.h>
#include <iostream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

Window::Window(const std::string& title)
  : Window(800, 600, title) {}

Window::Window(int width, int height, const std::string& title)
  : m_width(width), m_height(height), m_title(title) {}

bool Window::init() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_win = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
  if (!m_win) {
    std::cout << "Failed to create GLFW window\n";
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(m_win);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD\n";
    return false;
  }

  glViewport(0, 0, m_width, m_height);
  glfwSetFramebufferSizeCallback(m_win, framebufferSizeCallback);

  return true;
}

bool Window::isClosed() const {
  return glfwWindowShouldClose(m_win);
}

void Window::readInput() const {
  processInput(m_win);
}

void Window::processFrame() const {
  glfwSwapBuffers(m_win);
  glfwPollEvents();
}

Window::~Window() {
  std::cout << "Window destroyed\n";
  glfwTerminate();
}


void framebufferSizeCallback(GLFWwindow*, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}