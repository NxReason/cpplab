#pragma once

namespace nxmath {

constexpr float PI = 3.141592653589793;

inline float deg_to_rad(float degrees) {
  return degrees / 180 * PI;
}

inline float rad_to_deg(float radians) {
  return radians / PI * 180;
}

}