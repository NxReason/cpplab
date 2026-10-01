add_library(imgui_dock STATIC
  imgui.cpp
  imgui_draw.cpp
  imgui_tables.cpp
  imgui_widgets.cpp

  backends/imgui_impl_glfw.cpp
  backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui_dock
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/backends
)

target_link_libraries(imgui_dock
  PUBLIC
    glfw
    opengl32
)