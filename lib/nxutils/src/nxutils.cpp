#include "nxutils.h"

namespace nxutils {

std::vector<int> range(int min, int max) {
  int count = max - min;
  std::vector<int> values(count);
  for (int i = 0; i < count; i++) {
    values[i] = i + min;
  }
  return values;
}


void repeat(int times, Action fn) {
  for (int i = 0; i < times; i++) {
    fn();
  }
}

}