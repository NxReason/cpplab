#pragma once

#include <iostream>

template <typename T>
T nxmax(T x, T y) {
  return (x < y) ? y : x;
}

template<typename T, typename U>
auto nxmin(T x, U y) {
  return (x < y) ? x : y;
}

auto nxavg(auto x, auto y);

template<int N>
void print() {
  std::cout << N << '\n';
}


template<typename T>
void printTimes(T val, int times=1) {
  while (times--) {
    std::cout << val << ' ';
  }
  std::cout << '\n';
}

template<int N>
constexpr int factorial() {
  if (N < 1) return 1;

  int product { 1 };
  for (int i { 2 }; i <= N; ++i) {
    product *= i;
  }
  return product;
}

template <typename T>
T addOne(T x);

template<typename T>
T mult(T x, int y) {
  return static_cast<int>(x * y);
}

void fnExample();
