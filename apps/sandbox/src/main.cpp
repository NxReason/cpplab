#include <iostream>

#include "nxid.h"

int main() {
  for (int i = 0; i < 100; ++i) {
    std::cout << nxid() << '\n';
  }

  return 0;
}