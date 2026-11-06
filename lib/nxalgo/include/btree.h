#pragma once

#include <iostream>
#include <queue>
#include <string>
#include <vector>

template <typename T>
class BTree {
public:
  struct Node {
    T value;
    Node* left;
    Node* right;
  };

  BTree() {};
  BTree(T root_value) {
    create_root(root_value);
  }
  BTree(Node* root) {
    m_root = copy_rec(root);
  }
  BTree(const BTree& other) = delete;

  ~BTree() {
    free_rec(m_root);
  };

  // Adding
  void add(T value) {
    if (m_root == nullptr) {
      create_root(value);
      return;
    }

    add_rec(m_root, value);
  }

  // User processing
  template <typename Action>
  void traverse_in(Action action) {
    traverse_in(m_root, action);
  }

  template <typename Action>
  void traverse_pre(Action action) {
    traverse_pre(m_root, action);
  }

  template <typename Action>
  void traverse_depth(Action action) {
    if (m_root == nullptr) return;

    std::queue<Node*> nodes{};
    nodes.push(m_root);

    while (!nodes.empty()) {
      auto node = nodes.front();
      nodes.pop();

      action(node->value);

      if (node->left != nullptr) nodes.push(node->left);
      if (node->right != nullptr) nodes.push(node->right);
    }
  }

  // Getting data
  std::vector<T> get_sorted_vector() {
    std::vector<T> result {};
    inorder(m_root, [&result](Node* node) { result.push_back(node->value); });
    return result;
  }

  std::vector<T> get_depth_vector() const {
    if (m_root == nullptr)
      return std::vector<T>{};

    std::vector<Node*> nodes{};
    std::vector<T> values{};
    nodes.push_back(m_root);
    size_t index = 0;
    while (index < nodes.size()) {
      auto node = nodes[index];
      if (node->left != nullptr) nodes.push_back(node->left);
      if (node->right != nullptr) nodes.push_back(node->right);
      values.push_back(node->value);
      index++;
    }

    return values;
  }

  BTree<T> get_subtree(T new_root) const {
    return BTree<T> { find_node(new_root) };
  }


  // Finding
  Node* find_node(T value) const {
    return find_node_rec(m_root, value);
  }

  Node** find_node_pointer(T value) {
    return find_node_pointer_rec(&m_root, value);
  }

  bool contains(T value) {
    return contains_rec(m_root, value);
  }

  // Deleting
  void remove(T value) {
    auto p_node = find_node_pointer(value);

    if (p_node == nullptr) return;

    auto node = *p_node;
    // Leaf
    if (node->left == nullptr && node->right == nullptr) {
      delete *p_node;
      *p_node = nullptr;
    }

    // 1 child
    if (node->left == nullptr && node->right != nullptr) {
      Node* child = node->right;
      delete *p_node;
      *p_node = child;
    }
    if (node->left != nullptr && node->right == nullptr) {
      Node* child = node->left;
      delete *p_node;
      *p_node = child;
    }

    // 2 children
    if (node->left != nullptr && node->right != nullptr) {
      // find max on the left tree
      Node** max_node = find_max_node(&(node->left));
      T max_value = (*max_node)->value;

      // replace it with its left branch (if any)
      Node* max_child = (*max_node)->left;
      delete *max_node;
      *max_node = max_child;

      // replace remove target with max 
      (*p_node)->value = max_value;
    }
  }

  // Utils
  size_t count() const {
    return m_count;
  }

  int height() {
    return height_rec(m_root, -1);
  };

  void print() const {
    print_rec(m_root, 0);
  }
private:
  Node* m_root { nullptr };
  size_t m_count { 0 };

  void create_root(T value) {
    m_root = new Node { value, nullptr, nullptr };
    m_count++;
  }

  void add_rec(Node* current, T value) {
    if (current->value > value) {
      if (current->left != nullptr) add_rec(current->left, value);
      else current->left = new Node { value, nullptr, nullptr };
    }
    else {
      if (current->right != nullptr) add_rec(current->right, value);
      else current->right = new Node { value, nullptr, nullptr };
    }
    m_count++;
  }

  void print_rec(Node* node, int depth) const {
    if (node == nullptr) return;

    print_rec(node->left, depth + 1);
    std::cout << std::string(depth * 4, ' ') << node->value << '\n';
    print_rec(node->right, depth + 1);
  }

  int height_rec(Node* node, int depth) {
    if (node == nullptr) return depth;

    depth++;
    int h_left = height_rec(node->left, depth);
    int h_right = height_rec(node->right, depth);

    return h_left > h_right ? h_left : h_right;
  }

  Node* find_node_rec(Node* node, const T& value) {
    if (node == nullptr) return nullptr;

    if (value < node->value) return find_node_rec(node->left, value);
    if (value > node->value) return find_node_rec(node->right, value);
    return node;
  }

  Node** find_node_pointer_rec(Node** node, const T& value) {
    if (*node == nullptr) return nullptr;

    if (value < (*node)->value) return find_node_pointer_rec(&((*node)->left), value);
    if (value > (*node)->value) return find_node_pointer_rec(&((*node)->right), value);
    return node;
  }

  Node** find_max_node(Node** node) {
    if (*node == nullptr) return nullptr;

    while ((*node)->right != nullptr) node = &((*node)->right);
    return node;
  }

  bool contains_rec(Node* node, T value) {
    if (node == nullptr) return false;

    if (node->value > value) return contains_rec(node->left, value);
    if (node->value < value) return contains_rec(node->right, value);
    return true;
  }

  void free_rec(Node* node) {
    if (node == nullptr) return;

    free_rec(node->left);
    free_rec(node->right);
    delete node;
  }

  Node* copy_rec(Node* node) {
    if (node == nullptr) return nullptr;

    Node* copy = new Node { node->value, nullptr, nullptr };
    copy->left = copy_rec(node->left);
    copy->right = copy_rec(node->right);
    return copy;
  }

  // General traversal functions
  template<typename Action>
  void inorder(Node* node, Action action) {
    if (node == nullptr) return;

    inorder(node->left, action);
    action(node);
    inorder(node->right, action);
  }

  template<typename Action>
  void traverse_in(Node* node, Action action) {
    if (node == nullptr) return;

    traverse_in(node->left, action);
    action(node->value);
    traverse_in(node->right, action);
  }


  template<typename Action>
  void traverse_pre(Node* node, Action action) {
    if (node == nullptr) return;

    action(node->value);
    traverse_pre(node->left, action);
    traverse_pre(node->right, action);
  }
};