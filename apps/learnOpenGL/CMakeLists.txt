add_app(learnOpenGL)

target_link_libraries(learnOpenGL PRIVATE
  glad
  glfw
  imgui
  opengl32
  gdi32
  user32)