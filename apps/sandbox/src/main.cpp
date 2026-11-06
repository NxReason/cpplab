#include "graph.h"
#include <string>
#include <iostream>

struct Entity {
  int id;
  std::string name;
};
std::ostream& operator<<(std::ostream& out, const Entity& e) {
  out << "Entity{" << e.id << ", " << e.name << "}";
  return out;
}
bool operator==(const Entity& left, const Entity& right) {
  return (left.id == right.id) && (left.name == right.name);
}
bool operator!=(const Entity& left, const Entity& right) {
  return !(left == right);
}

void print_entity_name(const Entity& e) {
  std::cout << e.name << '\n';
}

int main() {
  Entity e1 { 1, "foo" };
  Entity e2 { 2, "bar" };
  Entity e3 { 3, "baz" };
  Entity e4 { 4, "qux" };
  Entity e5 { 5, "wix" };
  Entity e6 { 6, "hut" };

  AdjList<Entity> al{};
  al.add_nodes({ e1, e2, e3, e4, e5, e6 });

  al.add_edge(e1, e2);
  al.add_edge(e1, e3);
  al.add_edge(e2, e4);
  al.add_edge(e2, e3);
  al.add_edge(e4, e6);
  al.add_edge(e4, e1);

  al.print();

  std::cout << "BFS:" << '\n';
  auto res = bfs(al, e1, print_entity_name);
  for (const auto index: res) {
    std::cout << index << '\n';
  }

  return 0;
}