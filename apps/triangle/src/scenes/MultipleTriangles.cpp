#include "Scene.h"
#include "sprites/Triangle.h"



MultipleTriangles::MultipleTriangles() {
  Triangle* topleft = new Triangle { 
    Vector3{ -0.9, 0.9 },
    Vector3{ -0.9, 0.6 },
    Vector3{ -0.6, 0.9 }
  };
  Triangle* topright = new Triangle {
    Vector3 { 0.9, 0.9 },
    Vector3 { 0.6, 0.9 },
    Vector3 { 0.9, 0.6 },
  };
  Triangle* bottomleft = new Triangle {
    Vector3 { -0.9, -0.9 },
    Vector3 { -0.9, -0.6 },
    Vector3 { -0.6, -0.9 },
  };
  Triangle* bottomright = new Triangle {
    Vector3 { 0.9, -0.9 },
    Vector3 { 0.9, -0.6 },
    Vector3 { 0.6, -0.9 },
  };
  sprites.push_back(topleft);
  sprites.push_back(topright);
  sprites.push_back(bottomleft);
  sprites.push_back(bottomright);
}