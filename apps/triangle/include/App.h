#pragma once

#include "Window.h"
#include "EditorUI.h"
#include "Renderer.h"
#include "Scene.h"

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
  std::string currentSceneName;
  IScene* currentScene;
  void updateCurrentScene();
};