#include "CliOutput.h"
#include <iostream>

void clio::printTitle(const std::string& title) {
  std::cout << "###  " << title << "  ###" << std::endl;
}
void clio::printEnd() {
  std::cout << "###  Done!  ###" << std::endl;
}