#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include <common/Types.h>

#include "Logger.h"
#include "CliOutput.h"

int main() {
  Logger logger;
  clio::printTitle("Hello World");

  std::cout << "Hello, World!" << std::endl;
  std::cout << std::filesystem::current_path() << '\n';

  u32 value = 42;
  std::cout << value << std::endl;


  std::ifstream file("assets/hello.txt");
  if (!file) {
    std::cerr << "Failed to open file\n";
    return 1;
  }
  std::string line;
  while (std::getline(file, line)) {
    std::cout << line << '\n';
  }
  return 0;
}