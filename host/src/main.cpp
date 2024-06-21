#include <SDL3/SDL.h>
#include <expected>
#include <filesystem>
#include <format>
#include <iostream>

#include <chimera/flecs.h>
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

    auto* window = SDL_CreateWindow("hello world", 1920, 1080, SDL_WINDOW_VULKAN);
    auto* rend   = SDL_CreateRenderer(window, nullptr);

    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);

    bool quit = false;
    while(!quit) {
        SDL_Event e;
        while(SDL_PollEvent(&e) != SDL_FALSE) {
            switch(e.type) {
            case SDL_EVENT_KEY_DOWN:
                if(e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    quit = true;
                }
            default:
                break;
            }
        }

        SDL_RenderClear(rend);
        SDL_RenderPresent(rend);
    }

    SDL_DestroyWindow(window);
    return 0;
}
