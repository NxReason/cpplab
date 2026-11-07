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

using Graph = AdjListWeight<Entity>;

class Temp {
public:
  Temp() {
    std::cout << "Def constructed" << '\n';
  }
};

int main() {
  Graph g;

  auto ids = g.add_nodes({
    Entity { 1, "foo" },
    Entity { 2, "bar" },
    Entity { 3, "baz" },
    Entity { 4, "qux" },
    Entity { 5, "wiz" },
    Entity { 6, "kek" },
    Entity { 7, "lol" }
  });

  g.add_edge(ids[0], ids[1], 6);
  g.add_edge(ids[0], ids[2], 2);
  g.add_edge(ids[1], ids[3], 3);
  g.add_edge(ids[2], ids[1], 1);
  g.add_edge(ids[2], ids[3], 5);


  auto path = shortest_path(g, ids[0], ids[3]);
  for (const auto& node_id : path) {
    std::cout << (*g.node(node_id)).value << '\n';
  }

  std::cout << "Distances from: " << (*g.node(ids[0])).value << '\n';
  auto distances = shortest_distances(g, ids[0]);
  for (const auto& [id, dist] : distances) {
    auto node = g.node(id);
    std::cout << '\t' << (*node).value << " - " << dist << '\n';
  }

  return 0;
}