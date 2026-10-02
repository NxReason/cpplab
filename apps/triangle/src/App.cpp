#include "App.h"

#include <glad/glad.h>

App::App()
  : window { 1440, 800 }, ui { window } {
}

void App::run() {
  renderer.setClearColor();
  while (!window.shouldClose()) {
    window.pollEvents();
    ui.newFrame();
    ui.draw();

    renderer.setViewport(calculateViewport());
    renderer.render();

    ui.render();
    window.swapBuffers();
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