#include "UI.h"
#include "imgui.h"

#include <iostream>

UI::UI(const Window& window) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(window.getGlfwWindow(), true);
  ImGui_ImplOpenGL3_Init("#version 330");
}

UI::~UI() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void UI::newFrame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();

  ImGui::NewFrame();
  ImGui::SetNextWindowPos(ImVec2(0, 0));
  float height = ImGui::GetIO().DisplaySize.y;
  ImGui::SetNextWindowSizeConstraints(ImVec2(200, height), ImVec2(600, height));
}

void UI::draw() {
  ImGui::Begin("Scene", nullptr, imGuiWindowFlags);
  if (ImGui::Button("Save")) {
    saveFunc();
  }

  const char* scenes[] = { "Triangle", "Square" };
  static int itemCurrent = 0;
  ImGui::Combo("Scenes", &itemCurrent, scenes, IM_COUNTOF(scenes));

  width = ImGui::GetWindowWidth();
  ImGui::End();
}

void UI::render() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

float UI::getWidth() const {
  return width;
}

void UI::saveFunc() {
  std::cout << "saving" << std::endl;
  std::cout << width << std::endl;
}