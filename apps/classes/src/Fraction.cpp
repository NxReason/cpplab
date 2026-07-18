#include "Fraction.h"
#include <iostream>


Fraction::Fraction(int numerator, int denominator)
  : m_num { numerator }, m_den { denominator } {}

Fraction::Fraction(const Fraction& f)
  : m_num { f.m_num }, m_den { f.m_den } {
  std::cout << "Copied\n";
}

void Fraction::print() const {
  std::cout << "Fraction(" << m_num << ", " << m_den << ")\n";
}

void printFraction(Fraction f) { f.print(); }
Fraction generateFraction(int n, int d) {
  Fraction f { n, d };
  return f;
}

void fractionEx() {
  Fraction f { 5, 2 };
  f.print();
  printFraction(f);

  Fraction f2 { generateFraction(1, 2) };
  f2.print();
  printFraction(f2);
}