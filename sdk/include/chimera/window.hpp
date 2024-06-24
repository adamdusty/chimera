#pragma once

#include <cstdint>
#include <expected>
#include <memory>
#include <string>

#include <SDL3/SDL.h>

#include <chimera/sdk/export.hpp>

namespace chimera::sdk {

enum class window_flags : std::uint64_t {
    none               = 0,
    fullscreen         = SDL_WINDOW_FULLSCREEN,
    opengl             = SDL_WINDOW_OPENGL,
    vulkan             = SDL_WINDOW_VULKAN,
    metal              = SDL_WINDOW_METAL,
    hidden             = SDL_WINDOW_HIDDEN,
    borderless         = SDL_WINDOW_BORDERLESS,
    resizable          = SDL_WINDOW_RESIZABLE,
    minimized          = SDL_WINDOW_MINIMIZED,
    maximized          = SDL_WINDOW_MAXIMIZED,
    mouse_grabbed      = SDL_WINDOW_MOUSE_GRABBED,
    occluded           = SDL_WINDOW_OCCLUDED,
    input_focus        = SDL_WINDOW_INPUT_FOCUS,
    mouse_focus        = SDL_WINDOW_MOUSE_FOCUS,
    external           = SDL_WINDOW_EXTERNAL,
    modal              = SDL_WINDOW_MODAL,
    high_pixel_density = SDL_WINDOW_HIGH_PIXEL_DENSITY,
    mouse_capture      = SDL_WINDOW_MOUSE_CAPTURE,
    always_on_top      = SDL_WINDOW_ALWAYS_ON_TOP,
    utility            = SDL_WINDOW_UTILITY,
    tooltip            = SDL_WINDOW_TOOLTIP,
    popup_menu         = SDL_WINDOW_POPUP_MENU,
    keyboard_grabbed   = SDL_WINDOW_KEYBOARD_GRABBED,
    transparent        = SDL_WINDOW_TRANSPARENT,
    not_focusable      = SDL_WINDOW_NOT_FOCUSABLE,
};

struct window_desc {
    std::string title  = "Chimera";
    int32_t width      = 1920;
    int32_t height     = 1080;
    window_flags flags = window_flags::none;
};

constexpr auto sdl_window_deleter = [](SDL_Window* win) {
    SDL_DestroyWindow(win);
};

struct CHIMERA_EXPORT window {
    std::unique_ptr<SDL_Window, decltype(sdl_window_deleter)> handle;

    auto size() const -> std::pair<uint32_t, uint32_t>;

    static auto create(const window_desc& desc) -> std::expected<window, std::string> {
        auto* window_handle =
            SDL_CreateWindow(desc.title.c_str(), desc.width, desc.height, static_cast<SDL_WindowFlags>(desc.flags));

        if(window_handle == nullptr) {
            return std::unexpected("Unable to create window");
        }

        return window{
            .handle = std::unique_ptr<SDL_Window, decltype(sdl_window_deleter)>(window_handle, sdl_window_deleter),
        };
    }
};

} // namespace chimera::sdk