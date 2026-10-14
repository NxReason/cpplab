#include <iostream>
#include <string>
#include <unordered_map>

class Entity {
public:
  std::string name { "nxr" };
};

int main() {
  std::unordered_map<std::string, Entity*> e_map;
  e_map["foo"] = new Entity{};

  return 0;
}