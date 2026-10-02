#include "Window.h"

#include <GLFW/glfw3.h>
#include <cassert>
#include <stdexcept>

Window::Window(int width, int height, const char* title) {
  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(
    width,
    height,
    title,
    nullptr,
    nullptr
  );

  if (!window) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }

  glfwSetWindowUserPointer(window, this);
  glfwMakeContextCurrent(window);

  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glfwSetKeyCallback(window, keyCallback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwDestroyWindow(window);
    glfwTerminate();
    throw std::runtime_error("Failed to initialize GLAD");
  }

  framebufferSize = { width, height };
  glViewport(0, 0, width, height);
}

Window::~Window() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void Window::pollEvents() const {
  glfwPollEvents();
}

void Window::swapBuffers() const {
  glfwSwapBuffers(window);
}

bool Window::shouldClose() const {
  return glfwWindowShouldClose(window);
}

FramebufferSize Window::getFramebufferSize() const {
  return framebufferSize;
}

GLFWwindow* Window::getGlfwWindow() const {
  return window;
}

void Window::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
  assert(self != nullptr);
  self->framebufferSize = { width, height };
}

void Window::keyCallback(GLFWwindow* window, int key, int /* scancode */, int action, int /* mods */) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}