#include "input.h"

std::set<fs::path> collect_inputs(const std::vector<std::string>& inputs) {
  auto current = fs::absolute(".");

  std::set<fs::path> result;

  for (const auto& input : inputs) {
    auto path = fs::absolute(input);

    if (fs::is_directory(path)) {
      auto dir_iter = fs::directory_iterator(path);
      for (const auto& entry : dir_iter) {
        if (entry.is_regular_file() && entry.path().extension() == ".png") {
          result.insert(entry);
        }
      }
    }
    else {
      result.insert(path);
    }
  }

  return result;
}