#include <filesystem>
#include <iostream>
#include <vector>

#include <chimera/sdk.hpp>

#include "plugin.hpp"
#include "utils.hpp"

/*
    - Get available plugin manifests
    - Get available pack manifests
    - Plugin management
    - Plugin function pointer loading
    - Execution loop
*/

auto main() -> int {
    auto exe_dir    = chimera::get_executable_dir();
    auto pack_dir   = exe_dir / "packs";
    auto plugin_dir = exe_dir / "plugins";

    auto plugin_manifests = chimera::search_for_plugin_manifests(plugin_dir);

    auto plugins = std::vector<chimera::plugin>();
    for(const auto& dir: std::filesystem::directory_iterator(plugin_dir)) {
        auto plugin_res = chimera::load_plugin(dir);
        if(!plugin_res) {
            std::cerr << plugin_res.error() << '\n';
        }
        plugins.emplace_back(std::move(*plugin_res));
    }

    auto ctx = chimera::context{.a = 64, .b = 8};
    for(const auto& plg: plugins) {
        std::cerr << plg.manifest.nspace << ':' << plg.manifest.name << '\n';
        plg.on_load(ctx);
        plg.execute(ctx);
    }

    return 0;
}