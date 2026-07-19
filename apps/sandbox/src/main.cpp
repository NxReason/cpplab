#include "nxrng.h"
#include "nxutils.h"
#include <iostream>

using rng = nxrng::Random;

int main() {
  auto printRandom = []() {
    std::cout << rng::Int(5, 15) << '\n';
  };
  nxutils::repeat(10, printRandom);
  return 0;
}