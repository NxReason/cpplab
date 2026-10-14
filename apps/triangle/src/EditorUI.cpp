#include "EditorUI.h"
#include "imgui.h"

EditorUI::EditorUI(const Window& window) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(window.getGlfwWindow(), true);
  ImGui_ImplOpenGL3_Init("#version 330");
}

EditorUI::~EditorUI() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void EditorUI::newFrame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();

  ImGui::NewFrame();
  ImGui::SetNextWindowPos(ImVec2(0, 0));
  float height = ImGui::GetIO().DisplaySize.y;
  ImGui::SetNextWindowSizeConstraints(ImVec2(200, height), ImVec2(600, height));
}

void EditorUI::draw() {
  ImGui::Begin("Scene", nullptr, imGuiWindowFlags);

  drawSceneCombo();
  drawPolygonCheckbox();

  width = ImGui::GetWindowWidth();
  ImGui::End();
}

void EditorUI::drawSceneCombo() {
  if (scenes.size() == 0) {
    ImGui::Text("No scenes");
    return;
  }

  auto comboPreview = scenes[currentScene];
  if (ImGui::BeginCombo("Scenes", comboPreview.c_str())) {
    for (size_t n = 0; n < scenes.size(); ++n) {
      const bool isSelected = (currentScene == n);
      if (ImGui::Selectable(scenes[n].c_str(), isSelected)) {
        currentScene = n;
      }
      if (isSelected) {
        ImGui::SetItemDefaultFocus();
      }
    }
    ImGui::EndCombo();
  }
}

void EditorUI::drawPolygonCheckbox() {
  ImGui::Checkbox("Polygon mode", &isPolygon);
}

void EditorUI::render() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

float EditorUI::getWidth() const {
  return width;
}

void EditorUI::setScenes(const std::vector<std::string>& names, size_t current) {
  scenes = names;
  currentScene = current;
}

size_t EditorUI::getCurrentSceneIndex() const {
  return currentScene;
}

std::string EditorUI::getCurrentSceneName() const {
  return scenes[currentScene];
}

bool EditorUI::getIsPolygon() const {
  return isPolygon;
}