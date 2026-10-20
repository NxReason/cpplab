#include "nxalgo.h"

int gcd(int a, int b) {
  while (b != 0) {
    int rem = a % b;
    a = b;
    b = rem;
  }
  return a;
}

unsigned long long fast_power(int base, int pow) {
  switch (pow) {
    case 0: return 1;
    case 1: return base;
    case 2: return base * base;
  }

  int shift = 2;
  unsigned long long result = base;
  while (shift < pow) {
    result *= result;
    shift <<= 1;
  }
  return result * fast_power(base, pow - (shift >> 1));
}