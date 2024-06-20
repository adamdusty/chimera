#include "plugin/loading.hpp"

#include <fstream>

namespace fs = std::filesystem;

namespace chimera {

// Find all plugin manifest paths in plugin directory `p`
auto find_manifests(const fs::path& p) -> std::vector<fs::path> {
    auto manifest_paths = std::vector<fs::path>();

    // Iterate through plugin namespaces
    for(const auto& namespace_entry: fs::directory_iterator{p}) {

        // Iterate through plugin names
        for(const auto& name_entry: fs::directory_iterator(namespace_entry)) {

            // Iterate through versions
            for(const auto& version_entry: fs::directory_iterator(name_entry)) {
                if(fs::exists(version_entry.path() / "plugin.json")) {
                    manifest_paths.emplace_back(version_entry.path() / "plugin.json");
                }
            }
        }
    }

    return manifest_paths;
}

auto load_manifests(const std::vector<fs::path>& paths) -> std::vector<chimera::plugin_manifest> {
    auto manifests = std::vector<plugin_manifest>();
    for(const auto& p: paths) {
        auto file_stream   = std::ifstream(p);
        auto string_stream = std::stringstream();
        string_stream << file_stream.rdbuf();

        if(auto mani_res = plugin_manifest::from_json(string_stream.str())) {
            manifests.emplace_back(*mani_res);
        }
    }

    return manifests;
}

auto load_plugins(const fs::path& plugin_dir, const std::vector<plugin_manifest>& manifests) -> std::vector<plugin> {
    auto plugins = std::vector<plugin>();

    for(const auto& man: manifests) {
        auto bin_path = plugin_dir / man.nspace / man.name / man.plugin_version /
                        std::format("{}.{}", man.executable_name, LIB_EXT);

        if(auto plg = load_plugin(bin_path)) {
            plg->manifest = man;
            plugins.emplace_back(std::move(*plg));
        }
    }

    return plugins;
}

} // namespace chimera