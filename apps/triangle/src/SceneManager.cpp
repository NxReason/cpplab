#include "Scene.h"

SceneManager::SceneManager() {
  defaultScene = "Basic Triangle";
  scenes["Basic Triangle"] = new TriangleScene;
  scenes["Square No IBO"] = new SquareScene;
}

void SceneManager::add(const std::string& name, IScene* scene) {
  scenes[name] = scene;
}

IScene* SceneManager::get(const std::string& name) {
  return scenes.at(name);
}

IScene* SceneManager::getDefaultScene() const {
  return scenes.at(defaultScene);
}

std::string SceneManager::getDefaultSceneName() const {
  return defaultScene;
}

std::vector<std::string> SceneManager::getSceneNames() const {
  std::vector<std::string> names;
  for (const auto& pair : scenes) {
    names.push_back(pair.first);
  }
  return names;
}

size_t SceneManager::getDefaultSceneIndex() const {
  auto names = getSceneNames();
  for (size_t i = 0; i < names.size(); ++i) {
    if (names[i] == defaultScene) {
      return i;
    }
  }
  return 0;
}