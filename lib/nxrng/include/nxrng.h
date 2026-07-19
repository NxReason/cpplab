#pragma once

#include <algorithm>
#include <random>

namespace nxrng {

int randomInt(int min, int max);
float randomFloat(float min, float max);
double randomDouble(double min, double max);
bool randomBool();

template <typename C, typename T>
T pick(C container) {
  static std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<size_t> dist(0, container.size() - 1);
  return container[dist(gen)];
}
template <typename C>
void shuffle(C container) {
  static std::mt19937 gen(std::random_device{}());
  std::shuffle(container.begin(), container.end(), gen);
}

class Random {
public:
  static int Int(int min, int max);
private:
  static std::mt19937& generator();
};

}