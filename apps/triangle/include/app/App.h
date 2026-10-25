#pragma once

#include "ResourceManager.h"
#include "app/Window.h"
#include "app/EditorUI.h"
#include "graphics/Renderer.h"

class App {
public:
  App();
  void run();
private:
  Window window;
  Renderer renderer;
  Settings ui_settings;
  Settings current_settings;
  EditorUI ui;
  ResourceManager resource_manager;

  Viewport calc_viewport() const;
  void update_settings();
};