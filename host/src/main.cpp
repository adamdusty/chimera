#include <SDL3/SDL.h>
#include <expected>
#include <filesystem>

#include <chimera/flecs.h>
#include <chimera/sdk.hpp>
#include <spdlog/spdlog.h>

#include "plugin.hpp"
#include "utils.hpp"

auto main() -> int {
    auto exe_dir    = chimera::get_executable_dir();
    auto pack_dir   = exe_dir / "packs";
    auto plugin_dir = exe_dir / "plugins";

    auto manifest_paths = chimera::find_manifests(plugin_dir);
    auto manifests      = chimera::load_manifests(manifest_paths);
    auto plugins        = chimera::load_plugins(plugin_dir, manifests);

    auto context = chimera::sdk::context();

    for(const auto& plg: plugins) {
        if(plg.on_load != nullptr) {
            plg.on_load(context);
        }
    }

    for(const auto& plg: plugins) {
        if(plg.execute != nullptr) {
            plg.execute(context);
        }
    }

    auto desc = chimera::sdk::window_desc{};
    auto win  = chimera::sdk::window::create(desc);

    return 0;
}
