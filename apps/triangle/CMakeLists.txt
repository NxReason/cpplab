add_app(triangle)

target_link_libraries(triangle PRIVATE
  glad
  glfw
  imgui_dock
  opengl32
  gdi32
  user32)