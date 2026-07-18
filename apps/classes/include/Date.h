#pragma once

#include <string_view>
class Date {
private:
  int m_day{};
  int m_month{};
  int m_year{};
public:
  void print();
  void print(std::string_view prefix);

  int getDay() const;
  void setDay(int day);

  int getMonth() const;
  void setMonth(int month);

  int getYear() const;
  void setYear(int year);
};

void dateEx();
