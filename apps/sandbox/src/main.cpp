#include <string>
#include <vector>

#include "nxbench.h"

std::vector<int> DoWork() {
  std::vector<int> squares {};
  for (int i = 0; i < 100000; i++) {
    squares.push_back(i * i);
  }
  return squares;
}

int main() {
  const std::string fnName { "DoWork" };
  nxbench::measure([]() {
    DoWork();
  });

  nxbench::measure([]() {
    DoWork();
  });
  return 0;
}