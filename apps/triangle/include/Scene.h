#pragma once

#include <vector>
#include <map>
#include <string>

#include "sprites/ISprite.h"

class IScene;
using SceneMap = std::map<std::string, IScene*>;

class SceneManager {
public:
  std::string DEFAULT_SCENE;

  SceneManager();

  void add(const std::string& name, IScene* scene);
  IScene* get(const std::string& name);

  IScene* getDefaultScene() const;
  std::string getDefaultSceneName() const;
  size_t getDefaultSceneIndex() const;

  std::vector<std::string> getSceneNames() const;
private:
  SceneMap scenes;
  std::string defaultScene;
};

class IScene {
public:
  virtual std::vector<ISprite*> getSprites() const;
protected:
  std::vector<ISprite*> sprites;
};

class TriangleScene : public IScene {
public:
  TriangleScene();
};

class SquareScene : public IScene {
public:
  SquareScene();
};