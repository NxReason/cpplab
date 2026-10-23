#include "nxdlist.h"
#include <iostream>
#include <vector>


int main() {
  // DList<int> list { 4, 8, 15, 16 };
  DList<int> list { std::vector<int> { 4, 8, 15, 16, 23, 42 } };

  for (size_t i = 0; i < list.get_count(); ++i) {
    std::cout << i << " = " << list[i] << '\n';
  }

  std::cout << list << '\n';

  return 0;
}