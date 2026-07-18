#pragma once

class Fraction {
public:
  Fraction(int numerator = 0, int denominator = 1);
  Fraction(const Fraction& f);

  void print() const;
private:
  int m_num { 0 };
  int m_den { 1 };
};

void printFraction(Fraction f);
Fraction generateFraction(int n, int d);

void fractionEx();