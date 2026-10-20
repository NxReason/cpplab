#pragma once

#include <concepts>
#include <initializer_list>
#include <iostream>
#include <optional>
#include <ranges>
#include <stdexcept>
#include <utility>


template <typename T>
class SList {
private:
  struct Item {
    T value;
    Item *next;
  };

public:
  SList() = default;


  SList(T value)
    : m_count { 1 } {
    m_head = new Item { value };
  }


  template <typename It>
  SList(It first, It last) {
    if (first == last) return;

    while (first != last) {
      append(*first);
      first++;
    }
  }


  template <typename... Args>
    requires (std::convertible_to<Args, T> && ...)
  SList(Args&&... args) {
    (append(std::forward<Args>(args)), ...);
  }


  SList(std::initializer_list<T> values) {
    for (const T& value: values) {
      append(value);
    }
  }


  template <std::ranges::input_range R>
    requires std::convertible_to<std::ranges::range_reference_t<R>, T>
  SList(const R& range)
    : SList(std::ranges::begin(range), std::ranges::end(range)) {}


  SList(const T* c_arr, int count) {
    for (int i = 0; i < count; ++i) {
      append(c_arr[i]);
    }
  }


  ~SList() {
    auto iter = m_head;
    while (iter != nullptr) {
      auto current = iter;
      iter = iter->next;
      delete current;
    }
  }


  // Adding items
  void append(const T& value) {
    auto item = new Item { value, nullptr };
    m_count++;
    if (m_head == nullptr) {
      m_head = item;
      m_tail = item;
      return;
    }

    m_tail->next = item;
    m_tail = item;
  }


  void prepend(const T& value) {
    auto item = new Item { value, nullptr };
    m_count++;
    if (m_head == nullptr) {
      m_head = item;
      m_tail = item;
      return;
    }

    item->next = m_head;
    m_head = item;
  }


  void insert_at(const T& value, size_t pos) {
    if (pos > m_count) {
      throw std::out_of_range("SingleList::insert_at - position is out of range");
    }

    if (pos == 0) {
      prepend(value);
      return;
    }
    if (pos == m_count) {
      append(value);
      return;
    }

    auto iter = m_head;
    size_t index = 0;
    while (iter != nullptr) {
      if (index == pos - 1) {
        auto new_item = new Item { value, iter->next };
        iter->next = new_item;
        m_count++;
        break;
      }
      index++;
      iter = iter->next;
    }
  }


  // Indexing
  T at(size_t pos) const {
    if (pos >= m_count) {
      throw std::out_of_range("SingleList::at - position is out of range");
    }

    auto iter = m_head;
    size_t index = 0;
    while (index != pos) {
      iter = iter->next;
      index++;
    }

    return iter->value;
  }


  T operator[](size_t pos) const {
    return at(pos);
  }
  
  // Setting
  void set_at(const T& value, size_t pos) {
    if (pos >= m_count) {
      throw std::out_of_range("SingleList::at - position is out of range");
    }

    auto iter = m_head;
    size_t index = 0;
    for (; index != pos; ++index, iter = iter->next);

    iter->value = value;
  }


  // Finding
  std::optional<size_t> find_index(const T& value) const {
    size_t index = 0;

    for (auto iter = m_head; iter != nullptr; iter = iter->next, ++index) {
      if (iter->value == value) return index;
    }

    return std::nullopt;
  }


  std::optional<T> find(bool (*predicate)(T)) {
    for (auto iter = m_head; iter != nullptr; iter = iter->next) {
      if (predicate(iter->value)) return iter->value;
    }

    return std::nullopt;
  }


  std::optional<T> find(bool (*predicate)(T), size_t& index) {
    index = 0;

    for (auto iter = m_head; iter != nullptr; iter = iter->next, ++index) {
      if (predicate(iter->value)) return iter->value;
    }

    return std::nullopt;
  }


  // Taking / removing
  T take_head() {
    if (m_count == 0) {
      throw std::runtime_error("SingleList::take_head - list is empty");
    }

    auto head_ptr = m_head;
    m_head = m_head->next;
    if (m_count == 1) {
      m_tail = nullptr;
    }

    m_count--;

    // may throw for some types
    T head_value = std::move(head_ptr->value);
    delete head_ptr;
    return head_value;
  }


  T take_tail() {
    if (m_count == 0) {
      throw std::runtime_error("SingleList::take_tail - list is empty");
    }

    auto tail_ptr = m_tail;

    if (m_count == 1) {
      m_head = nullptr;
      m_tail = nullptr;
    }
    else {
      auto prev = m_head;
      while (prev->next != m_tail) prev = prev->next;
      m_tail = prev;
      prev->next = nullptr;
    }

    m_count--;

    T head_value = std::move(tail_ptr->value);
    delete tail_ptr;
    return head_value;
  }


  T take_at(size_t pos) {
    if (pos >= m_count) {
      throw std::out_of_range("SingleList::take_at - position is out of range");
    }
    if (m_count == 0) {
      throw std::runtime_error("SingleList::take_at - list is empty");
    }

    if (pos == 0) { return take_head(); }

    auto prev = m_head;
    for (size_t index = 1; index < pos; ++index, prev = prev->next);
    auto result_ptr = prev->next;
    prev->next = result_ptr->next;

    T result_value = std::move(result_ptr->value);
    delete result_ptr;
    m_count--;
    return result_value;
  }


  // Filter / map / reduce / any / all
  SList<T> filter(bool (*predicate)(T)) const {
    SList filtered {};

    auto iter = m_head;
    while (iter != nullptr) {
      if (predicate(iter->value)) {
        filtered.append(iter->value);
      }
      iter = iter->next;
    }

    return filtered;
  }


  template <typename NewType>
  SList<NewType> map(NewType (*fn)(T)) const {
    SList<NewType> mapped {};

    auto iter = m_head;
    while (iter != nullptr) {
      mapped.append(fn(iter->value));
      iter = iter->next;
    }

    return mapped;
  }


  template <typename AccT>
  AccT reduce(AccT(*reducer)(AccT acc, T curr), AccT initial = T{}) const {
    auto iter = m_head;
    while (iter != nullptr) {
      initial = reducer(initial, iter->value);
      iter = iter->next;
    }
    return initial;
  }


  bool all(bool (*predicate)(T)) const {
    auto iter = m_head;
    while (iter != nullptr) {
      if (!predicate(iter->value)) return false;
      iter = iter->next;
    }
    return true;
  }


  void for_each(void (*fn)(T)) const {
    auto iter = m_head;
    while (iter != nullptr) {
      fn(iter->value);
      iter = iter->next;
    }
  }

  // Getters
  Item* get_head() const { return m_head; }
  Item* get_tail() const { return m_tail; }
  size_t count() const { return m_count; }

  // Properties
private:
  Item* m_head { nullptr };
  Item* m_tail { nullptr };
  size_t m_count { 0 };

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
    return Iterator(m_head);
  }
  Iterator end() const {
    return Iterator(nullptr);
  }

  Iterator find_iter(const T& value) {
    for (auto iter = m_head; iter != nullptr; iter = iter->next) {
      if (iter->value == value) return Iterator(iter);
    }

    return Iterator(nullptr);
  }
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const SList<T>& list) {
  for (const auto& val : list) {
    out << val << " -> ";
  }
  out << "nullptr";
  return out;
}
