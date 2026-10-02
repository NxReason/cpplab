#pragma once

#include "Window.h"
#include "UI.h"
#include "Renderer.h"

class App {
public:
  App();
  void run();
private:
  Window window;
  Renderer renderer;
  UI ui;

  Viewport calculateViewport() const;
};