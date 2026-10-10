#include "NxMath.h"
#include "Scenes.h"

TriangleScene::TriangleScene() {
  Triangle top { 
    Vector2 { .x = -0.5, .y = 0.5 },
    Vector2 { .x = -0.5, .y = 0.0 },
    Vector2 { .x =  0.0, .y = 0.5 },
  };
  Triangle bottom { 
    Vector2 { .x = 0.5, .y =  0.5 },
    Vector2 { .x = 0.5, .y =  0.0 },
    Vector2 { .x = 0.0, .y =  0.0 },
  };
  triangles.push_back(top);
  triangles.push_back(bottom);
}

std::vector<Triangle> TriangleScene::getTriangles() const {
  return triangles;
}