#pragma once

#include <chrono>
#include <limits>


namespace nxbench {
  struct Params {
    int iters { 100 };
    const std::string& name { "" };
  };

  struct Results {
    double total;
    double min;
    double max;
  };

  void printOutput(const Params& params, const Results& results);

  template <typename Fn>
  void measure(Fn&& fn, const Params& params = { 100, "" }) {
    // preheat
    for (int i = 0; i < 1000; i++) {
      fn();
    }

    double min { std::numeric_limits<double>::max() }, max { 0.0 }, total { 0.0 };
    for (int i = 0; i < params.iters; i++) {
      auto start = std::chrono::steady_clock::now();
      fn();
      auto end = std::chrono::steady_clock::now();
      double ms = std::chrono::duration<double, std::milli>(end - start).count();
      if (ms < min) min = ms;
      if (ms > max) max = ms;
      total += ms;
    }

    printOutput(params, Results{ total, min, max });
  }
}