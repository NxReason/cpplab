#include "nxbench.h"

#include <iostream>

namespace nxbench {
  void printOutput(const Params& params, const Results& results) {
    std::cout << params.name;
    if (!params.name.empty()) std::cout << ": ";

    std::cout << "total [" << results.total << "ms], ";
    std::cout << "avg [" << results.total / params.iters << "ms], ";
    std::cout << "min [" << results.min << "], ";
    std::cout << "max [" << results.max << "]\n";
  }
}

