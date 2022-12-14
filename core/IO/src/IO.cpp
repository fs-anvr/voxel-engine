// clang-format off

#include <IO/IO.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// clang-format on

namespace VoxelEngine {

std::string IO::FromFile(std::string filePath) {
  std::string result;
  std::fstream stream(filePath, std::ios::in);
  result.assign(std::istreambuf_iterator<char>(stream),
                std::istreambuf_iterator<char>());
  stream.close();
  return result;
}

}  // namespace VoxelEngine
