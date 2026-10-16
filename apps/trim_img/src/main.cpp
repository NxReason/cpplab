#include <vector>

#include "input.h"
#include "Image.h"
#include "CliArgs.h"

int main(int argc, char** argv) {
  nxcli::CliArgs args { argc, argv };
  auto in_paths = collect_inputs(args.get_inputs());

  std::vector<Image> images {};
  for (const auto& in_path : in_paths) {
    images.emplace_back(Image { in_path });
  }

  for (auto& img : images) {
    img.calc_opaque_rect();
    img.write();
    img.free();
  }

  return 0;
}