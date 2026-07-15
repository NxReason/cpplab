#include "Logger.h"
#include <iostream>

Logger::Logger() {
  std::cout << "App started" << std::endl;
}
Logger::~Logger() {
  std::cout << "App finished" << std::endl;
}