#include "Date.h"
#include <iostream>

void Date::print() {
  std::cout << m_day << '/' << m_month << '/' << m_year;
}
void Date::print(std::string_view prefix) {
  std::cout << prefix << m_day << '/' << m_month << '/' << m_year;
}

int Date::getDay() const {
  return m_day;
}
void Date::setDay(int day) {
  m_day = day;
}

int Date::getMonth() const {
  return m_month;
}
void Date::setMonth(int month) {
  m_month = month;
}

int Date::getYear() const {
  return m_year;
}
void Date::setYear(int year) {
  m_year = year;
}

void dateEx() {
  Date d{};
  d.setDay(10);
  d.setMonth(12);
  d.setYear(2025);
  d.print();
}