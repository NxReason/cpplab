#pragma once

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Window.h"

class UI {
public:
  UI(const Window& window);
  ~UI();
  void newFrame();
  void draw();
  void render();
  float getWidth() const;
  void saveFunc();
private:
  float width {};
  const int imGuiWindowFlags = 
    ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoCollapse;
};