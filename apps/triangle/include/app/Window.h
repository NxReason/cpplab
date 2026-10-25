#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct FramebufferSize {
  int width;
  int height;
};

class Window {
public:
  Window(int width, int height, const char* title = "Triangle");
  ~Window();

  bool should_close() const;
  void poll_events() const;
  void swap_buffers() const;

  GLFWwindow* glfw_window() const;
  FramebufferSize framebuffer_size() const;
private:
  GLFWwindow* m_window;
  FramebufferSize m_framebuffer_size;

  static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
