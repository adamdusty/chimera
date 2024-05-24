#pragma once

#include <filesystem>
#include <vector>

#include "manifest.hpp"

namespace chimera {

auto find_available_plugins(const std::filesystem::path& plugin_dir) -> std::vector<plugin_manifest>;

}