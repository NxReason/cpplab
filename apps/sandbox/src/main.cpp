#include "Vector.h"

using namespace nxmath;

void showVectorExamples() {
  Vector3 v { 1, 2, 0 };
  Vector3 axis { 5, 0, 0 };

  std::cout << axis.proj(v) << '\n';
}

int main() {
  showVectorExamples();

  return 0;
}