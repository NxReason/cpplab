#include "ValueCategory.h"

#include <iostream>

static int g_Value = 42;

int& getValue() {
  return g_Value;
}

int getint() { return 5; }

void valueCategoryEx() {
  getValue() = 10;
  std::cout << g_Value << '\n';

  PRINTVCAT(5);
  PRINTVCAT(getint());
  int x { 5 };
  PRINTVCAT(x);
  PRINTVCAT(std::string { "Hello" });
  PRINTVCAT("Hello");
  PRINTVCAT(++x);
  PRINTVCAT(x++);
}