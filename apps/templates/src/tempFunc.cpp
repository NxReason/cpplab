#include "tempFunc.h"

#include <iostream>
#include <string>

template<>
float nxmax<float>(float x, float y) {
  std::cout << "Finding max float" << '\n';
  return (x < y) ? y : x;
}

template<>
const char* nxmax(const char* x, const char* y) = delete;

auto nxavg(auto x, auto y) {
  return (x + y) / 2;
}

template<>
bool mult(bool x, int y) {
  return x && y;
}

void fnExample() {
  std::cout << nxmax(7, 2) << '\n';
  std::cout << nxmax(15.2f, 12.4f) << '\n';
  std::cout << nxmax(15.2, 12.4) << '\n';
  std::cout << nxmax<double>(5, 2.5) << '\n';
  std::string foo { "foo" };
  std::string bar { "bar" };
  std::cout << nxmax(foo, bar) << std::endl;

  std::cout << nxmin(7, 2.5) << '\n';

  std::cout << nxavg(7, 2.5) << '\n';
  std::cout << nxavg(7, 2) << '\n';

  print<5>();
  print<'c'>();

  std::cout << factorial<0>() << '\n';
  std::cout << factorial<3>() << '\n';
  std::cout << factorial<5>() << '\n';
  std::cout << factorial<-3>() << '\n';

  std::cout << addOne(2) << '\n';
  std::cout << addOne(5) << '\n';

  printTimes("foo", 4);

  std::cout << mult(42.5, 5) << '\n';
  std::cout << mult(8, 5) << '\n';
  std::cout << mult(true, 5) << '\n';
}


template<typename T>
T addOne(T x) { return x + 1; }