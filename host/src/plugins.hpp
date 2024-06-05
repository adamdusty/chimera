#pragma once

#include <filesystem>
#include <vector>

#include "manifest.hpp"

namespace chimera {

auto find_available_plugins(const std::filesystem::path& plugin_dir) -> std::vector<plugin_manifest>;

struct plugin {
    std::string nspace;
    std::string name;
    std::filesystem::path executable;
    version plugin_version;

    // library_handle
    // fn ptr to library on_load
    // fn ptr to library execute
    // fn ptr to library on_unload
};

} // namespace chimera