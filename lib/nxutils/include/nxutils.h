#pragma once

#include <vector>
namespace nxutils {

using Action = void (*)();

std::vector<int> range(int min, int max);
void repeat(int times, Action fn);

}