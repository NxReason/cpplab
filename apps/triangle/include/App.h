#pragma once

#include "SceneManager.h"
#include "Window.h"
#include "EditorUI.h"
#include "Renderer.h"

class App {
public:
  App();
  void run();
private:
  Window window;
  Renderer renderer;
  EditorUI ui;
  SceneManager sceneManager;

  Viewport calculateViewport() const;
};