#include "tempClass.h"

#include <iostream>

void tempClassEx() {
  Pair<int> p1{ 5, 6 };
  std::cout << p1 << '\n';
  Pair<double> p2{ 1.2, 3.4 };
  std::cout << p2 << '\n';
  Pair<bool> p3{ true, false };
  std::cout << p3 << '\n';

  std::cout << max(p1) << '\n';
  std::cout << max(p2) << '\n';
  
  Point point { 15.9, 356.3 };
  print(point);
  print(p1);
}