#include <iostream>
#include <string>

class Entity {
public:
  std::string name { "nxr" };
};

int main() {
  Entity e;
  std::cout << e.name << '\n';

  return 0;
}