#include "app/App.h"

#include <glad/glad.h>

App::App()
  : window { 1440, 800 }, ui { window } { }


void App::run() {
  renderer.clear_color();

  renderer.gen_resources();
  while (!window.should_close()) {
    window.poll_events();
    ui.new_frame();
    ui.draw();

    renderer.set_viewport(calc_viewport());
    renderer.render();

    ui.render();
    window.swap_buffers();
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
