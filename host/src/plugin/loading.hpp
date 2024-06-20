#pragma once

#include <filesystem>
#include <vector>

#include "plugin/plugin.hpp"

namespace chimera {

auto find_manifests(const std::filesystem::path& p) -> std::vector<std::filesystem::path>;
auto load_manifests(const std::vector<std::filesystem::path>& paths) -> std::vector<chimera::plugin_manifest>;
auto load_plugins(const std::filesystem::path& plugin_dir, const std::vector<plugin_manifest>& manifests)
    -> std::vector<plugin>;

} // namespace chimera