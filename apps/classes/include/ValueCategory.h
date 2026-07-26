#pragma once

int& getValue();

template <typename T>
constexpr bool is_lvalue(T&) { return true; }

template <typename T>
constexpr bool is_lvalue(T&&) { return false; }

#define PRINTVCAT(expr) { std::cout << #expr << " is an " << (is_lvalue(expr) ? "lvalue\n" : "rvalue\n"); }


void valueCategoryEx();


