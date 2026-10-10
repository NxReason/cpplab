#pragma once

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <string>
#include <vector>

#include "Window.h"

class EditorUI {
public:
  EditorUI(const Window& window);
  ~EditorUI();
  void newFrame();
  void draw();
  void render();
  float getWidth() const;
private:
  float width {};
  const int imGuiWindowFlags = 
    ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoCollapse;

  std::vector<std::string> scenes = {};
  size_t currentScene = 0;

  void drawSceneCombo();
};