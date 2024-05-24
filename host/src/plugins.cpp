#include "plugins.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

namespace chimera {

auto find_available_plugins(const std::filesystem::path& plugin_dir) -> std::vector<plugin_manifest> {
    auto manifests = std::vector<plugin_manifest>();

    for(const auto& dir: fs::directory_iterator(plugin_dir)) {
        auto manifest_path = dir.path() / "plugin.json";
        if(!fs::exists(manifest_path)) {
            continue;
        }

        auto manifest_stream = std::ifstream(manifest_path);
        if(!manifest_stream) {
            // Notify?
            continue;
        }

        auto manifest_string_stream = std::stringstream();
        manifest_string_stream << manifest_stream.rdbuf();

        if(auto manifest = plugin_manifest::from_json(manifest_string_stream.str())) {
            manifests.emplace_back(*manifest);
        }
    }

    return manifests;
}

} // namespace chimera