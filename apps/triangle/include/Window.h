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

  bool shouldClose() const;
  void pollEvents() const;
  void swapBuffers() const;

  GLFWwindow* getGlfwWindow() const;
  FramebufferSize getFramebufferSize() const;
private:
  GLFWwindow* window;
  FramebufferSize framebufferSize;

  static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
  static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};