#pragma once

class Pair {
public:
  int first;
  int second;

  void print() const;
  bool isEqual(const Pair& other) const;
};

void pairEx();