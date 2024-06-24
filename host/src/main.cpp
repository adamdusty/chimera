#include <SDL3/SDL.h>
#include <expected>
#include <filesystem>
#include <format>
#include <iostream>

#include <chimera/flecs.h>
#include <chimera/sdk.hpp>
#include <spdlog/spdlog.h>

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

    auto manifest_paths = chimera::find_manifests(plugin_dir);
    auto manifests      = chimera::load_manifests(manifest_paths);
    for(const auto& m: manifests) {
        std::cout << std::format("{}:{}\n", m.nspace, m.name);
    }

    auto plugins = chimera::load_plugins(plugin_dir, manifests);

    auto context = chimera::context();

    for(const auto& plg: plugins) {
        plg.on_load(context);
    }

    for(const auto& plg: plugins) {
        plg.execute(context);
    }

    auto desc = chimera::window_desc{};
    auto win  = chimera::window::create(desc);

    spdlog::set_level(spdlog::level::info);
    spdlog::info("Starting...");

    return 0;
}
