#include "app/Window.h"

#include <GLFW/glfw3.h>
#include <cassert>
#include <stdexcept>

Window::Window(int width, int height, const char* title) {
  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(
    width,
    height,
    title,
    nullptr,
    nullptr
  );

  if (!m_window) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }

  glfwSetWindowUserPointer(m_window, this);
  glfwMakeContextCurrent(m_window);

  glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
  glfwSetKeyCallback(m_window, key_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwDestroyWindow(m_window);
    glfwTerminate();
    throw std::runtime_error("Failed to initialize GLAD");
  }

  m_framebuffer_size = { width, height };
  glViewport(0, 0, width, height);
}

Window::~Window() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
}

void Window::poll_events() const {
  glfwPollEvents();
}

void Window::swap_buffers() const {
  glfwSwapBuffers(m_window);
}

bool Window::should_close() const {
  return glfwWindowShouldClose(m_window);
}

FramebufferSize Window::framebuffer_size() const {
  return m_framebuffer_size;
}

GLFWwindow* Window::glfw_window() const {
  return m_window;
}

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
  assert(self != nullptr);
  self->m_framebuffer_size = { width, height };
}

void Window::key_callback(GLFWwindow* window, int key, int /* scancode */, int action, int /* mods */) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}