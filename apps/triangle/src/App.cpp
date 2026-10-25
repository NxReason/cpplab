#include "app/App.h"
#include "Scenes.h"

#include <glad/glad.h>

App::App()
  : window { 1440, 800 }, ui { window, &ui_settings } { }


void App::run() {
  renderer.clear_color();
  TriangleScene scene;

  resource_manager.gen_resources(&scene);
  while (!window.should_close()) {
    window.poll_events();
    ui.new_frame();
    ui.draw();

    renderer.set_viewport(calc_viewport());
    renderer.render(resource_manager, &scene);

    ui.render();
    window.swap_buffers();

    update_settings();
  }
}

Viewport App::calc_viewport() const {
  auto fmb_size = window.framebuffer_size();
  auto ui_width = static_cast<int>(ui.get_width());

  return Viewport { 
    .x = ui_width,
    .y = 0,
    .width = fmb_size.width - ui_width, 
    .height = fmb_size.height
  };
}

void App::update_settings() {
  if (ui_settings.is_polygon != current_settings.is_polygon) {
    current_settings.is_polygon = ui_settings.is_polygon;
    renderer.set_polygon_mode(current_settings.is_polygon);
  }
}
