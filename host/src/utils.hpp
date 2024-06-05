#pragma once

#include <filesystem>
#include <plugin.hpp>

namespace chimera {

auto get_executable_dir() -> std::filesystem::path;
auto get_plugin_executable_path(const std::filesystem::path& plugin_dir, const plugin_manifest& man)
    -> std::filesystem::path;

} // namespace chimera