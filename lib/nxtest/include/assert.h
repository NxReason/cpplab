#pragma once

#include <algorithm>
#include <sstream>
#include <stdexcept>

namespace nxtest::assert {

template <typename T>
void equal(T expected, T got) {
  if (expected == got) return;

  std::ostringstream oss;
  oss << "Expected: " << expected << ", got: " << got;
  throw std::logic_error(oss.str());
}

template <typename T>
void greater(T expected, T got) {
  if (got > expected) return;

  std::ostringstream oss;
  oss << got << " should be > " << expected;
  throw std::logic_error(oss.str());
}

template <typename T>
void less(T expected, T got) {
  if (got < expected) return;

  std::ostringstream oss;
  oss << got << " should be < " << expected;
  throw std::logic_error(oss.str());
}

template <typename T>
void gte(T expected, T got) {
  if (got >= expected) return;

  std::ostringstream oss;
  oss << got << " should be >= " << expected;
  throw std::logic_error(oss.str());
}

template <typename T>
void lte(T expected, T got) {
  if (got <= expected) return;

  std::ostringstream oss;
  oss << got << " should be <= " << expected;
  throw std::logic_error(oss.str());
}

template <typename T>
void isNull(T got) {
  if (got == nullptr) return;

  std::ostringstream oss;
  oss << got << " should be null";
  throw std::logic_error(oss.str());
}

template <typename T>
void notNull(T got) {
  if (got != nullptr) return;

  std::ostringstream oss;
  oss << got << " should not be null";
  throw std::logic_error(oss.str());
}

template <typename T>
void strContains(T whole, T sub) {
  if (whole.contains(sub)) return;

  std::ostringstream oss;
  oss << "'" << whole << "' should contain '" << sub << "'";
  throw std::logic_error(oss.str());
}

template <typename T>
void strStarts(T whole, T sub) {
  if (whole.starts_with(sub)) return;

  std::ostringstream oss;
  oss << "'" << whole << "' should start with '" << sub << "'";
  throw std::logic_error(oss.str());
}

template <typename T>
void strEnds(T whole, T sub) {
  if (whole.ends_with(sub)) return;

  std::ostringstream oss;
  oss << "'" << whole << "' should end with '" << sub << "'";
  throw std::logic_error(oss.str());
}

template <typename T>
void isEmpty(T container) {
  if (container.size() == 0) return;

  throw std::logic_error("Container should be empty");
}

template <typename T>
void notEmpty(T container) {
  if (container.size() != 0) return;

  throw std::logic_error("Container should have elements");
}

template <typename T>
void size(long long unsigned count, T container) {
  if (container.size() == count) return;

  std::ostringstream oss;
  oss << "Container should have " << count << " elements, actual size: " << container.size();
  throw std::logic_error(oss.str());
}

template <typename Cont, typename T>
void contains(const Cont& c, const T& value) {
  if (std::find(c.begin(), c.end(), value) != c.end()) return;

  std::ostringstream oss;
  oss << "Container should have " << value;
  throw std::logic_error(oss.str());
}

}