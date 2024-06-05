#include <filesystem>
#include <format>
#include <iostream>
#include <unordered_map>

#include <chimera/sdk.hpp>

#include "library.hpp"
#include "plugin.hpp"
#include "utils.hpp"

using execute_proc = void (*)(const chimera::context&);

/*
    - Get available plugin manifests
    - Get available pack manifests
*/

auto main() -> int {
    auto exe_dir    = chimera::get_executable_dir();
    auto pack_dir   = exe_dir / "packs";
    auto plugin_dir = exe_dir / "plugins";

    std::cerr << exe_dir.string() << '\n';
    std::cerr << pack_dir.string() << '\n';
    std::cerr << plugin_dir.string() << '\n';

    auto plugin_manifests = chimera::search_for_plugin_manifests(plugin_dir);

    auto plugins = std::unordered_map<std::string, chimera::library>{};
    for(const auto& man: plugin_manifests) {
        auto this_plugin_dir = std::format(
            "{}-{}-{}.{}.{}",
            man.nspace,
            man.name,
            man.plugin_version.major,
            man.plugin_version.minor,
            man.plugin_version.patch
        );
        auto path = plugin_dir / this_plugin_dir / std::format("{}{}", man.executable_name, chimera::plugin_file_ext);
        std::cerr << "PLUGIN: " << path.string() << '\n';
        if(auto lib = chimera::load_library(path)) {
            plugins[std::format("{}:{}", man.nspace, man.name)] = std::move(*lib);
        }
    }

    for(const auto& [name, _]: plugins) {
        std::cerr << name << '\n';
    }

    return 0;
}