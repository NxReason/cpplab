add_app(triangle)

target_link_libraries(triangle PRIVATE
  glad
  glfw
  imgui
  opengl32
  gdi32
  user32)