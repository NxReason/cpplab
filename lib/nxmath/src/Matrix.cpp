#include "Matrix.h"

#include "cmath"

namespace nxmath {
  using std::sin;
  using std::cos;

  Matrix<4, 4> scale(float x, float y, float z) {
    return Matrix<4, 4> {{
      { x, 0, 0, 0 },
      { 0, y, 0, 0 },
      { 0, 0, z, 0 },
      { 0, 0, 0, 1 },
    }};
  }

  Matrix<4, 4> scale(float s) {
    return Matrix {{
      { s, 0, 0, 0 },
      { 0, s, 0, 0 },
      { 0, 0, s, 0 },
      { 0, 0, 0, 1 }
    }};
  }

  Mat4 translate(float x, float y, float z) {
    return Mat4 {{
      { 1, 0, 0, x },
      { 0, 1, 0, y },
      { 0, 0, 1, z },
      { 0, 0, 0, 1 },
    }};
  }

  Mat4 rotateX(float angleRad) {
    return Mat4 {{
      { 1, 0, 0, 0 },
      { 0, cos(angleRad), -sin(angleRad), 0 },
      { 0, sin(angleRad), cos(angleRad), 0 },
      { 0, 0, 0, 1 }
    }};
  }

  Mat4 rotateY(float angleRad) {
    return Mat4 {{
      { cos(angleRad), 0, sin(angleRad), 0, },
      { 0, 1, 0, 0 },
      { -sin(angleRad), 0, cos(angleRad), 0 },
      { 0, 0, 0, 1 }
    }};
  }

  Mat4 rotateZ(float angleRad) {
    return Mat4 {{
      { cos(angleRad), -sin(angleRad), 0, 0 },
      { sin(angleRad), cos(angleRad), 0, 0 },
      { 0, 0, 1, 0 },
      { 0, 0, 0, 1 }
    }};
  }

  Vector3 operator*(Mat4 m, Vector3 v) {
    float v4[4] { v.x, v.y, v.z, 1.0f };
    float out[4] { 0, 0, 0, 0 };
    for (size_t r = 0; r < 4; ++r) {
      for (size_t c = 0; c < 4; ++c) {
        out[r] += v4[c] * m(r, c);
      }
    }
    return Vector3 { out[0], out[1], out[2] };
  }
}