#pragma once
#include <random>
#include <utility>

int gcd(int a, int b);

template <typename Arr>
void randomize_arr(Arr &arr) {
  std::mt19937 gen(std::random_device {} ());
  std::uniform_int_distribution<size_t> dist(0, arr.size() - 1);

  for (size_t i = 0; i < arr.size(); ++i) {
    size_t j = dist(gen);
    std::swap(arr[i], arr[j]);
  }
}

unsigned long long fast_power(int base, int pow);