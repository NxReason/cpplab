#include "CliArgs.h"
#include <iostream>

using namespace nxcli;

int main(int argc, char** argv) {
  CliArgs args { argc, argv, {
    Arg { .name = "out", .t = typeid(bool) },
  } };
  args.summary();

  auto val = args.get_value<bool>("out");
  std::cout << val << '\n';

  return 0;
}