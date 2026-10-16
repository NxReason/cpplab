#pragma once

#include <set>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

std::set<fs::path> collect_inputs(const std::vector<std::string>& inputs);