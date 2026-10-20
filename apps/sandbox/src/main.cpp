#include "nxlist.h"
#include <iostream>


int main() {
  SList<int> list { 4, 8, 15, 16, 23, 42 };

  for (size_t i = 0; i < list.count(); ++i) {
    list.set_at(list[i] * 2, i);
  }
  std::cout << list << '\n';

  return 0;
}