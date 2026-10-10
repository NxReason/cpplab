#pragma once

#include <string>
#include <vector>

using StringList = std::vector<std::string>;

class SceneManager {
public:
  SceneManager();
  SceneManager(const char* scenes);
  SceneManager(const StringList& scenes);
private:
  StringList scenes;
};