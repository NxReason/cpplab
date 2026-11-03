#pragma once

#include <string>
#include <array>

using ConvertMap = std::array<char, 64>;
constexpr ConvertMap build_convert_map() {
  auto out_chars = ConvertMap{};
  int index = 0;

  for (char c = 'a'; c <= 'z'; c++) {
    out_chars[index++] = c;
  }
  for (char c = 'A'; c <= 'Z'; c++) {
    out_chars[index++] = c;
  }
  for (char c = '0'; c <= '9'; c++) {
    out_chars[index++] = c;
  }

  out_chars[index++] = '_';
  out_chars[index++] = '#';

  return out_chars;
}

constexpr auto convert_map = build_convert_map();


int get_bits(int from_value, size_t start_pos = 0, size_t count = 6);

std::string convert_dt();

std::string gen_random_part();

std::string nxid();
