#include <filesystem>
#include <format>
#include <iostream>
#include <vector>

#include <chimera/sdk.hpp>

#include "library.hpp"
#include "plugin.hpp"
#include "utils.hpp"

using execute_proc = void (*)(const chimera::context&);

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

    auto plugins = std::vector<chimera::library>{};
    for(const auto& man: plugin_manifests) {
        auto path = chimera::get_plugin_executable_path(plugin_dir, man);
        if(auto lib = chimera::load_library(path)) {
            plugins.emplace_back(std::move(*lib));
        }
    }

    for(const auto& lib: plugins) {
        std::cerr << lib << '\n';
    }

    return 0;
}