#include "nxrng.h"

#include <random>

namespace nxrng {

int randomInt(int min, int max) {
  static std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<int> dist(min, max);
  return dist(gen);
}

float randomFloat(float min, float max) {
  static std::mt19937 gen(std::random_device{}());
  std::uniform_real_distribution<float> dist(min, max);
  return dist(gen);
}

double randomDouble(double min, double max) {
  static std::mt19937 gen(std::random_device{}());
  std::uniform_real_distribution<double> dist(min, max);
  return dist(gen);
}

bool randomBool() {
  static std::mt19937 gen(std::random_device{}());
  std::bernoulli_distribution dist(0.5);
  return dist(gen);
}

// Static class impl
std::mt19937& Random::generator() {
  static std::mt19937 gen(std::random_device{}());
  return gen;
}

int Random::Int(int min, int max) {
  auto& gen = generator();
  std::uniform_int_distribution<int> dist(min, max);
  return dist(gen);
}

}