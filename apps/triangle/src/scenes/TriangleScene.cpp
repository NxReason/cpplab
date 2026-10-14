#include "Scene.h"
#include "sprites/Triangle.h"

#include "Vector.h"

TriangleScene::TriangleScene() {
  Triangle* t = new Triangle { 
    nxmath::Vector3{ -0.5f, -0.5f },
    nxmath::Vector3{ 0.5f, -0.5f },
    nxmath::Vector3{ 0.0f, 0.5f }
  };
  sprites.push_back(t);
}
