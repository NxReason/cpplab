#include "assert.h"
#include "test.h"
#include <vector>

using namespace nxtest;

int sum(int x, int y) {
  return x + y;
}

void testSum() {
  int result = sum(5, 2);
  assert::lte(6, result);
}
void testSum2() {
  int result = sum(10, 12);
  assert::lte(31, result);
}

void testNull() {
  void* foo = nullptr;
  assert::isNull(foo);
}

void stringTest() {
  const std::string text = "lorem ipsum dolor";
  const std::string sub = "sum";
  const std::string start = "lorem";
  const std::string end = "olor";
  assert::strContains(text, sub);
  assert::strStarts(text, start);
  assert::strEnds(text, end);
}

void containerTest() {
  std::vector<int> values{ 152, 4, 8, 15 };
  assert::size(4, values);
  assert::contains(values, 23);
}

int main() {
  test(testSum);
  test("Failure msg", testSum2);
  test("Null testing", testNull);
  test("String testing", stringTest);
  test("Container testing", containerTest);
  return 0;
}