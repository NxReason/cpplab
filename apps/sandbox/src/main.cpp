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

int main() {
  Entity e1 { 1, "foo" };
  Entity e2 { 2, "bar" };
  Entity e3 { 3, "baz" };
  Entity e4 { 4, "qux" };
  Entity e5 { 5, "wix" };
  AdjList<Entity> al{};
  al.add_node(e1);
  al.add_node(e2);
  al.add_nodes({ e3, e4 });
  al.add_node(e5);

  al.add_edge(e1, e2);
  al.add_edge(e1, e3);
  al.add_edge(e1, e4);
  al.add_edge(e1, e5);

  al.remove_node(e2);
  al.remove_node(e4);

  al.add_edge(e3, e5);

  al.print();
  std::cout << al.node_count() << '\n';
  std::cout << al.edge_count() << '\n';

  return 0;
}