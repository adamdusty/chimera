#pragma once

#include <filesystem>
#include <plugin.hpp>

namespace chimera {

auto get_executable_dir() -> std::filesystem::path;

} // namespace chimera