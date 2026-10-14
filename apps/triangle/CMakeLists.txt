add_app(triangle)

set(SHADER_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
set(SHADER_OUTPUT ${CMAKE_BINARY_DIR}/bin/triangle/shaders)
add_custom_target(triangleCopyShaders ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${SHADER_SOURCE}
    ${SHADER_OUTPUT}
  COMMENT "Syncing shader directory ..."
)
add_dependencies(triangle triangleCopyShaders)

target_link_libraries(triangle PRIVATE
  glad
  glfw
  imgui_dock
  nxmath
  opengl32
  gdi32
  user32)