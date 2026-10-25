#pragma once

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
  EditorUI ui;

  Viewport calc_viewport() const;
};