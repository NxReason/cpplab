#pragma once

#include <iostream>

template <typename T>
struct Pair {
  T first{};
  T second{};
};

struct Point {
  float first;
  float second;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Pair<T>& p) {
  os << "Pair(" << p.first << ", " << p.second << ")";
  return os;
}

template <typename T>
constexpr T max(Pair<T> p) {
  return p.first < p.second ? p.second : p.first;
}

template <typename T>
void print(T p) {
  std::cout << p.first << " / " << p.second << '\n';
}

void tempClassEx();