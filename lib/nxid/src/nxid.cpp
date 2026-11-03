#include "nxid.h"

#include <chrono>
#include <sstream>
#include <random>

int get_bits(int from_value, size_t start_pos, size_t count) {
  int result = 0;
  int current_bit = 1;
  for (size_t i = start_pos; i < start_pos + count; i++) {
    current_bit = 1 << i;
    current_bit &= from_value;
    result |= current_bit;
  }
  return result;
}


std::string convert_dt() {
  auto now = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(now);
  std::tm local = *std::localtime(&time);

  int year = local.tm_year + 1900;
  int month = local.tm_mon + 1;
  int day = local.tm_mday;

  int hour = local.tm_hour;
  int minute = local.tm_min;
  int second = local.tm_sec;
  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
    now.time_since_epoch()
  ).count() % 1000;

  std::stringstream dt {};

  dt << convert_map[get_bits(year, 6) >> 6];
  dt << convert_map[get_bits(year)];
  dt << convert_map[month];
  dt << convert_map[day];
  dt << convert_map[hour];
  dt << convert_map[minute];
  dt << convert_map[second];
  dt << convert_map[get_bits(ms, 5, 5) >> 5];
  dt << convert_map[get_bits(ms, 0, 5)];

  return dt.str();
}

std::string gen_random_part() {
  int count = 22;
  std::stringstream rnd {};
  static std::mt19937 gen(std::random_device{}());
  static std::uniform_int_distribution<int> dist(0, 61);

  for (int i = 0; i < count; ++i) {
    rnd << convert_map[dist(gen)];
  }

  return rnd.str();
}

std::string nxid() {
  auto dt = convert_dt();
  auto rnd = gen_random_part();
  std::string result = dt + "-" + rnd;
  return result;
}
