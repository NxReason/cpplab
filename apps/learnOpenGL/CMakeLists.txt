add_app(learnOpenGL)

set(SHADER_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
set(SHADER_OUTPUT ${CMAKE_BINARY_DIR}/bin/learnOpenGL/shaders)
add_custom_target(copyShaders ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${SHADER_SOURCE}
    ${SHADER_OUTPUT}
  COMMENT "Syncing shader directory ..."
)
add_dependencies(learnOpenGL copyShaders)

target_include_directories(learnOpenGL PRIVATE
  ${CMAKE_SOURCE_DIR}/external/stbi
  ${CMAKE_SOURCE_DIR}/external/glm)

target_include_directories(learnOpenGL PRIVATE
  ${CMAKE_SOURCE_DIR}/external/glm)

target_link_libraries(learnOpenGL PRIVATE
  glad
  glfw
  imgui
  opengl32
  gdi32
  user32)