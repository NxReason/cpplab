#pragma once
#include <string>

/*
TODO:
assert
- containers (empty, size, contains, start, end)

output
- total (success / fail / skip)
- output errors
  - exceptions
  - assert fail
*/

namespace nxtest {

void test(void (*testFn)());
void test(const std::string& desc, void (*testFn)());

}