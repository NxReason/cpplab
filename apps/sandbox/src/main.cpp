#include "nxdarray.h"
#include <iostream>


template <typename T>
void describe_arr(const Array<T>& values) {
  std::cout << "Count: " << values.count() << '\n';
  std::cout << "Capacity: " << values.capacity() << '\n';
  for (size_t i = 0; i < values.count(); ++i) {
    std::cout << values[i] << '\n';
  }
}

int main() {
  Array<int> values {4, 8, 15, 16, 23, 42};
  describe_arr(values);

  std::cout << values.take_at(2) << '\n';
  values.remove_at(3);
  describe_arr(values);

  auto bytes = 10000 * 10000 / 2 * sizeof(void*);
  auto kb = (float)bytes / 1024;
  auto mb = kb / 1024;
  auto gb = mb / 1024;
  std::cout << "bytes: " << bytes << '\n';
  std::cout << "kb: " << kb << '\n';
  std::cout << "mb: " << mb << '\n';
  std::cout << "gb: " << gb << '\n';

  return 0;
}