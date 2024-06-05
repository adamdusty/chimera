#pragma once

#include <expected>
#include <filesystem>
#include <string>
#include <vector>

#include "version.hpp"

namespace chimera {

#if defined(__WIN32) && __WIN32
#define WIN32_LEAN_AND_MEAN
constexpr auto plugin_file_ext = ".dll";
#elif defined(__linux__) && __linux__
constexpr auto plugin_file_ext = ".so";
#endif

struct plugin_manifest {
    std::string nspace;
    std::string name;
    std::string executable_name;
    version plugin_version;

    constexpr auto operator==(const plugin_manifest&) const -> bool = default;
    static auto from_json(const std::string_view str) -> std::expected<plugin_manifest, std::string_view>;
};

auto search_for_plugin_manifests(const std::filesystem::path& plugin_dir) -> std::vector<plugin_manifest>;

struct plugin_data {
    // Idea is to keep all the plugin data (enabled, name, version, etc.) in a struct attached to
    // the plugin ptr via a map or something.
};

} // namespace chimera