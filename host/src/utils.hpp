#pragma once

#include <filesystem>

namespace chimera {

auto get_executable_dir() -> std::filesystem::path;

}