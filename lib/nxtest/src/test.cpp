#include "test.h"
#include <iostream>
#include <stdexcept>

namespace nxtest {

void test(void (*testFn)()) {
  test("", testFn);
}

void test(const std::string& desc, void (*testFn)()) {
  try {
    testFn();
  }
  catch (std::logic_error ex) {
    if (desc != "") std::cout << "FAILURE: " << desc << std::endl;
    std::cout << ex.what() << std::endl;
  }
}

}