#pragma once
#include <optional>
#include <vector>
#include <iostream>

/*
* Adjacency list
* Adjacency matrix
* Implicit / graph grid

* add_node / remove_node
* add_edge / remove_edge
* has_edge
* get_node - by id / custom prop
* get_neighbors
* get_degree - count connections
* clear

* directed / undirected connections
* weighted / unweighted connections
* iterating over nodes and edges
* copy / move graph

* BFS
* DFS
* Iterative DFS
* Connected components
* Reachability

* BFS - shortest path in unweighted graphs
* Dijkstra - shortest path with non-negative weights
* A* - goal-directed pathfinding
* Bellman-Ford - shortest paths with negative weights

* Cycle detection - determine whether a cycle exists
* Topological sort - order vertices by dependencies
* Minimum spanning tree - connect all vertices with minimum total weight
* Strongly connected components - find mutually reachable groups in directed graphs
* Bipartite checking - determine whether vertices can be split into two groups
* Bridges and articulation points - find critical connections and vertices
*/

template<typename T>
class AdjList {
public:
  struct Node {
    T value;
    std::vector<size_t> edges {};
  };

  using Nodes = std::vector<Node>;

  // Adding / removing nodes
  void add_node(const T& node) {
    m_nodes.push_back(Node { .value = node });
  }

  void add_nodes(const std::vector<T>& nodes) {
    m_nodes.reserve(m_nodes.size() + nodes.size());
    for (const auto& node : nodes) {
      m_nodes.push_back(Node { node });
    }
  }

  size_t remove_node(const T& node) {
    return remove_nodes([&node](const T& val) { return val == node; });
  }

  template <typename Predicate>
  size_t remove_nodes(Predicate pred) {
    auto rm_indices = get_remove_indices(pred);
    size_t rm_count = std::erase_if(m_nodes, [&pred](Node& node) { return pred(node.value); });

    for (size_t i = 0; i < m_nodes.size(); ++i) {
      remove_edges(i, rm_indices);
      remap_edges(i, rm_indices);
    }

    return rm_count;
  }

  std::vector<size_t> get_remove_indices(const T& node) {
    std::vector<size_t> result{};
    for (size_t i = 0; i < m_nodes.size(); ++i) {
      if (m_nodes[i].value == node) result.push_back(i);
    }
    return result;
  }

  template<typename Predicate>
  std::vector<size_t> get_remove_indices(Predicate pred) {
    std::vector<size_t> result{};
    for (size_t i = 0; i < m_nodes.size(); ++i) {
      if (pred(m_nodes[i].value)) result.push_back(i);
    }
    return result;
  }

  // Adding / removing edges
  void add_edge(const T& from, const T& to) {
    auto from_index = get_node_index(from);
    auto to_index = get_node_index(to);

    if (from_index && to_index) m_nodes[*from_index].edges.push_back(*to_index);
  }

  void add_edge(size_t from, size_t to) {
    m_nodes[from].edges.push_back(to);
  }

  void remove_edge(const T& from, const T& to) {
    auto from_index = get_node_index(from);
    auto to_index = get_node_index(to);

    if (from_index && to_index) remove_edge(*from_index, *to_index);
  }

  void remove_edge(size_t from, size_t to) {
    Node& node = m_nodes[from];
    std::erase(node.edges, to);
  }

  void remove_edges(size_t from_idx, const std::vector<size_t>& indices) {
    Node& node = m_nodes[from_idx];
    for (const size_t index : indices) {
      std::erase(node.edges, index);
    }
  }

  void remap_edges(size_t from_idx, const std::vector<size_t>& rm_indices) {
    Node& node = m_nodes[from_idx];
    for (auto& edge : node.edges) {
      size_t offset = 0;
      for (const auto& rm_index : rm_indices) {
        if (edge > rm_index) offset++;
        else break;
      }
      edge -= offset;
    }
  }

  bool has_edge(size_t from, size_t to) const {
    const auto& edges = m_nodes[from].edges;
    auto found = std::find(edges.begin(), edges.end(), to);
    return found != edges.end();
  }

  // Getters
  std::optional<size_t> get_node_index(const T& node) const {
    size_t index = 0;
    for (const Node& n : m_nodes) {
      if (n.value == node) return index;
      index++;
    }
    return std::nullopt;
  }

  // TODO:
  void get_neighbors() {}
  void get_degree() {}

  // Utils
  void print() const {
    for (const Node& node : m_nodes) {
      std::cout << node.value << '\n';
      for (const size_t to : node.edges) {
        std::cout << '\t' << m_nodes[to].value << '\n';
      }
    }
  }

  size_t node_count() const { return m_nodes.size(); }

  size_t edge_count() const {
    size_t total = 0;
    for (const Node& node : m_nodes) {
      total += node.edges.size();
    }
    return total;
  }

  void clear() {
    m_nodes.clear();
  }

private:
  Nodes m_nodes;
};