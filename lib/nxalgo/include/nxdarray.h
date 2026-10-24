#pragma once

#include <initializer_list>
#include <cstddef>
#include <optional>

template <typename T>
class Array {
public:
  Array()
    : Array(4) {}

  Array(size_t capacity)
    : m_data { nullptr }, m_count { 0 }, m_capacity { capacity } {
    m_data = new T[capacity];
  }


  Array(std::initializer_list<T> values)
    : m_data { new T[values.size()] }, m_count { values.size() }, m_capacity { values.size() } {
    size_t index = 0;
    for (const T& val : values) {
      m_data[index] = val;
      ++index;
    }
  }


  Array(Array& other)
    : m_data { new T[other.m_capacity] }, m_count { other.m_count }, m_capacity { other.m_capacity } {
    for (size_t i = 0; i < m_count; ++i) {
      m_data[i] = other[i];
    }
  }


  ~Array() {
    delete[] m_data;
  }


  // Indexing
  T& operator[](size_t index) {
    return m_data[index];
  }


  const T& operator[](size_t index) const {
    return m_data[index];
  }


  // Adding
  void append(const T& value) {
    if (m_count >= m_capacity) {
      reallocate(m_capacity * 2);
    }
    m_data[m_count] = value;
    m_count++;
  }

  void insert_at(const T& value, size_t pos) {
    shift_right(pos);
    m_data[pos] = value;
    m_count++;
  }


  // Taking / Removing
  T take_head() {
    T value = m_data[0];

    shift_left();
    m_count--;

    return value;
  }


  T take_tail() {
    return m_data[--m_count];
  }


  T take_at(size_t pos) {
    T value = m_data[pos];

    shift_left(pos);
    m_count--;

    return value;
  }


  void remove_at(size_t pos) {
    shift_left(pos);
    m_count--;
  }


  // Finding
  std::optional<size_t> find(const T& search_value) const {
    for (size_t i = 0; i < m_count; ++i) {
      if (m_data[i] == search_value) return i;
    }
    return std::nullopt;
  }


  // Utils
  void fit() {
    reallocate(m_count);
  }

  // Getters
  size_t count() const { return m_count; }
  size_t capacity() const { return m_capacity; }
  T* data() const { return m_data; }
private:
  T* m_data { nullptr };
  size_t m_count { 0 };
  size_t m_capacity { 0 };

  void reallocate(size_t new_capacity) {
    m_capacity = new_capacity;
    auto new_data = new T[m_capacity];
    for (size_t i = 0; i < m_count; ++i) {
      new_data[i] = m_data[i];
    }
    delete[] m_data;
    m_data = new_data;
  }

  void shift_right(size_t from = 0) {
    if (m_count >= m_capacity) reallocate(m_capacity * 2);

    for (size_t i = m_count; i > from; --i) {
      m_data[i] = m_data[i - 1];
    }
  }

  void shift_left(size_t from = 0) {
    for (size_t i = from; i < m_count - 1; ++i) {
      m_data[i] = m_data[i + 1];
    }
  }
};