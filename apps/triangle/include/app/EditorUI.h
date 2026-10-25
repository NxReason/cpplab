#pragma once

#include <vector>
#include <string>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

#include "app/Window.h"

class EditorUI {
public:
  EditorUI(const Window& window);
  ~EditorUI();
  void new_frame();
  void draw();
  void render();
  float get_width() const;

  void set_scenes(const std::vector<std::string>& names);
private:
  float width {};
  const int imGuiWindowFlags = 
    ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoCollapse;

  std::vector<std::string> scenes = {};

  void draw_common_elements();
};