#pragma once
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
  Window(const std::string& title);
  Window(int width = 800, int height = 600, const std::string& title = "App Name");
  ~Window();

  bool init();
  bool isClosed() const;
  void processFrame() const;
  GLFWwindow* getWindow();
private:
  GLFWwindow* m_win;
  int m_width, m_height;
  std::string m_title;
};