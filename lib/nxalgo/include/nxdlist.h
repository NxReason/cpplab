#pragma once

#include <initializer_list>
#include <stdexcept>
#include <iostream>

template <typename T>
class DList {
private:
  struct Item {
    T value;
    Item* prev;
    Item* next;

    ~Item() {
      std::cout << "DList Item with value " << value << " deleted" << '\n';
    }
  };

public:
  DList(){
    init();
  }

  DList(DList& other) {
    init();
    for (const T& value : other) {
      append(value);
    }
  }

  
  template <typename It>
  DList(It first, It last) {
    init();
    if (first == last) return;

    while (first != last) {
      append(*first);
      first++;
    }
  }


  template <std::ranges::input_range R>
    requires std::convertible_to<std::ranges::range_reference_t<R>, T>
  DList(const R& range)
    : DList(std::ranges::begin(range), std::ranges::end(range)) {}


  DList(std::initializer_list<T> values) {
    init();
    for (const T& value: values) {
      append(value);
    }
  }


  ~DList() {
    while (m_head != nullptr) {
      auto to_del = m_head;
      m_head = m_head->next;
      delete to_del;
    }
  }


  // Adding
  void prepend(const T& value)  {
    add_item(value, m_head, m_head->next);
  }


  void append(const T& value) {
    add_item(value, m_tail->prev, m_tail);
  }


  void insert_at(const T& value, size_t pos) {
    if (pos > m_count) {
      throw std::out_of_range("DList::insert_at() - position is out of range");
    }
    auto prev = m_head;
    for (size_t index = 0; index != pos; ++index) prev = prev->next;

    add_item(value, prev, prev->next);
  }

  void insert_sorted(const T& value) {
    auto target = m_head->next;
    while (target != m_tail && target->value < value) target = target->next;
    add_item(value, target->prev, target);
  }


  // Indexing
  T at(size_t pos) const {
    if (pos >= m_count) {
      throw std::out_of_range("DList::at() - pos is out of range");
    }
    auto target = m_head->next;
    for (size_t i = 0; i < pos; ++i, target = target->next);

    return target->value;
  }


  T operator[](size_t pos) const {
    if (pos >= m_count) {
      throw std::out_of_range("DList::operator[] - pos is out of range");
    }

    return at(pos);
  }


  // Getters
  size_t get_count() const { return m_count; }


  T get_head() const {
    if (m_count == 0) {
      throw std::runtime_error("DList::get_head() - list is empty");
    }
    return m_head->next->value;
  }


  T get_tail() const {
    if (m_count == 0) {
      throw std::runtime_error("DList::get_tail() - list is empty");
    }
    return m_tail->prev->value;
  }
private:
  size_t m_count { 0 };
  Item* m_head { nullptr };
  Item* m_tail { nullptr };

  void init() {
    m_head = new Item { .value = 0, .prev = nullptr, .next = nullptr };
    m_tail = new Item { .value = 0, .prev = nullptr, .next = nullptr };
    m_head->next = m_tail;
    m_tail->prev = m_head;
  }

  void add_item(const T& value, Item* prev, Item* next) {
    auto new_item = new Item { value, prev, next };
    prev->next = new_item;
    next->prev = new_item;
    m_count++;
  }

  void set_link(Item* first, Item* second) {
    first->next = second;
    second->prev = first;
  }

// Iterator
private:
  class Iterator {
  private:
    Item* current;

  public:
    Iterator(Item* item) : current { item } {}

    T& operator*() const {
      return current->value;
    }

    Iterator& operator++() {
      current = current->next;
      return *this;
    }

    bool operator!=(const Iterator& other) const {
      return current != other.current;
    }
    bool operator==(const Iterator& other) const {
      return current == other.current;
    }
  };
public:
  Iterator begin() const {
    return Iterator(m_head->next);
  }
  Iterator end() const {
    return Iterator(m_tail);
  }

  Iterator find_iter(const T& value) {
    for (auto iter = m_head; iter != nullptr; iter = iter->next) {
      if (iter->value == value) return Iterator(iter);
    }

    return Iterator(nullptr);
  }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const DList<T>& list) {
  for (const T& value: list) {
    out << value << " -> ";
  }
  out << "nullptr";
  return out;
}