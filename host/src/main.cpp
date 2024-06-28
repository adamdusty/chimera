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

    spdlog::set_level(spdlog::level::info);
    spdlog::info("Searching for manifests...");

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

    auto desc = chimera::sdk::window_desc{
        .title  = "Chimera",
        .width  = 640,
        .height = 480,
        .flags  = chimera::sdk::window_flags::none,
    };
    auto win = chimera::sdk::window::create(desc);

    SDL_Renderer* rend = SDL_CreateRenderer(win->sdl_handle.get(), nullptr);
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);

    bool quit = false;
    SDL_Event e;
    while(!quit) {
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
            case SDL_EVENT_KEY_DOWN:
                if(e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    quit = true;
                }
                break;
            case SDL_EVENT_QUIT:
                quit = true;
            default:
                break;
            }
        }

        SDL_RenderClear(rend);
        SDL_RenderPresent(rend);

        for(const auto& plg: plugins) {
            if(plg.execute != nullptr) {
                plg.execute(context);
            }
        }
    }

    return 0;
}
