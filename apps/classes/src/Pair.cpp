#include "Pair.h"
#include <iostream>

void Pair::print() const {
  std::cout << "Pair(" << first << ", " << second << ")\n";
}

bool Pair::isEqual(const Pair& other) const {
  return first == other.first && second == other.second;
}

void pairEx() {
  const Pair p1 { 1, 2 };
  const Pair p2 { 3, 4 };

  std::cout << "p1: ";
  p1.print();

  std::cout << "p2: ";
  p2.print();

  std::cout << "p1 and p1 " << (p1.isEqual(p1) ? "are equal\n" : "are not equal\n");
  std::cout << "p1 and p2 " << (p1.isEqual(p2) ? "are equal\n" : "are not equal\n");
}