#include "Window.h"

#include <GLFW/glfw3.h>
#include <iostream>


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

  return true;
}

bool Window::isClosed() const {
  return glfwWindowShouldClose(m_win);
}

void Window::processFrame() const {
  glfwSwapBuffers(m_win);
  glfwPollEvents();
}

GLFWwindow* Window::getWindow() {
  return m_win;
}

Window::~Window() {
  std::cout << "Window destroyed\n";
  glfwTerminate();
}