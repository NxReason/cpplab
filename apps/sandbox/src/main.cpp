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
  Entity e_a { 1, "A" };
  Entity e_b { 2, "B" };
  Entity e_c { 3, "C" };
  Entity e_d { 4, "D" };
  Entity e_e { 5, "E" };
  Entity e_f { 6, "F" };

  AdjList<Entity> al{};
  al.add_nodes({ e_a, e_b, e_c, e_d, e_e, e_f });

  al.add_edge(e_a, e_b);
  al.add_edge(e_a, e_d);

  al.add_edge(e_b, e_c);
  al.add_edge(e_b, e_d);

  al.add_edge(e_c, e_f);

  al.add_edge(e_d, e_e);

  al.add_edge(e_e, e_f);

  al.print();

  std::cout << "BFS:" << '\n';
  auto bfs_res = bfs(al, e_a, print_entity_name);
  for (const auto index: bfs_res) {
    std::cout << index << '\n';
  }

  std::cout << "Path: " << '\n';
  auto path = shortest_path(al, e_a, e_f);
  for (const auto& step : path) {
    std::cout << al.get_node(step).value << '\n';
  }

  // std::cout << "DFS Iter:" << '\n';
  // auto dfs_res = dfs_iter(al, e1);
  // for (const auto index: dfs_res) {
  //   std::cout << index << '\n';
  // }

  // std::cout << "DFS Rec:" << '\n';
  // auto dfs_rec_res = dfs(al, e1);
  // for (const auto index: dfs_rec_res) {
  //   std::cout << index << '\n';
  // }

  return 0;
}