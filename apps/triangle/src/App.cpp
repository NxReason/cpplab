#include "App.h"
#include "Scene.h"

#include <glad/glad.h>

App::App()
  : window { 1440, 800 }, ui { window } { }


void App::run() {
  // TODO:
  // Update Shader classes
  // Dynamic getCoords / getVAO layout
  // UI / Scene interaction
  // Textures (shader + update sprite class)
  // View matrix
  // Scene update loop

  currentScene = sceneManager.getDefaultScene();
  renderer.setClearColor();
  renderer.generateResources(currentScene);

  currentSceneName = sceneManager.getDefaultSceneName();
  currentScene = sceneManager.getDefaultScene();
  ui.setScenes(sceneManager.getSceneNames(), sceneManager.getDefaultSceneIndex());

  while (!window.shouldClose()) {
    window.pollEvents();
    ui.newFrame();
    ui.draw();

    renderer.setViewport(calculateViewport());
    renderer.render(currentScene);

    ui.render();
    window.swapBuffers();

    updateCurrentScene();
  }
}

Viewport App::calculateViewport() const {
  auto fmbSize = window.getFramebufferSize();
  auto uiWidth = static_cast<int>(ui.getWidth());

  return Viewport { 
    .x = uiWidth,
    .y = 0,
    .width = fmbSize.width - uiWidth, 
    .height = fmbSize.height
  };
}

void App::updateCurrentScene() {
  std::string uiCurrent = ui.getCurrentSceneName();
  if (currentSceneName != uiCurrent) {
    currentSceneName = uiCurrent;
    currentScene = sceneManager.get(currentSceneName);
    renderer.generateResources(currentScene);
  }

  static bool isPoly = false;
  bool uiIsPoly = ui.getIsPolygon();
  if (isPoly != uiIsPoly) {
    isPoly = uiIsPoly;
    renderer.setPolygonMode(isPoly);
  }
}