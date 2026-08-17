#include "Vector.h"
#include "Matrix.h"
#include <cmath>

using namespace nxmath;

void showVectorExamples();

void showMatrixExample() {
  Matrix<3, 4> m {{
    { 2, 1, 3, 0 },
    { 0, 1, -1, 0 },
    { 1, 3, -1, 0 }
  }};

  auto sol = linearSystem(m);
  std::cout << sol;
}

int main() {
  showMatrixExample();

  return 0;
}

void showVectorExamples() {
  // 1.
  Vector3 p { 2, 2, 1 };
  Vector3 q { 1, -2, 0 };

  std::cout << "(a) " << dot(p, q) << '\n';
  std::cout << "(b) " << cross(p, q) << '\n';
  std::cout << "(c) " << proj(q, p) << '\n';

  // 2.
  float sqrt2 = std::sqrt(2);
  Vector3 e1 { sqrt2 / 2, sqrt2 / 2, 0 };
  Vector3 e2 { -1, 1, - 1};
  Vector3 e3 { 0, -2, - 2 };
  std::array<Vector3, 3> ortho = orthogonalize(e1, e2, e3);
  for (const auto& v : ortho) {
    std::cout << v << '\n';
  }
  std::cout << dot(ortho[0], ortho[1]) << '\n';
  std::cout << dot(ortho[0], ortho[2]) << '\n';
  std::cout << dot(ortho[1], ortho[2]) << '\n';

  // 3.
  Vector3 a1 { 1, 2, 3 };
  Vector3 a2 { -2, 2, 4 };
  Vector3 a3 { 7, -8, 6 };

  float area = 0.5 * (cross(
    a2 - a1,
    a3 - a1
  ).length());
  std::cout << "area " << area << '\n';
}