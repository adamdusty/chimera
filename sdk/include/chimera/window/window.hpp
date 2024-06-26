#pragma once

#include <cstdint>
#include <expected>
#include <memory>
#include <string>

#include <SDL3/SDL.h>

#include "chimera/window/raw_window.hpp"
#include <chimera/sdk/export.hpp>

namespace chimera::sdk {

enum class CHIMERA_EXPORT window_flags : std::uint64_t {
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

enum class gfx_backend {
    automatic,
    opengl,
    vulkan,
    dx12,
};

struct CHIMERA_EXPORT window_create_options {
    std::string title   = "Chimera";
    int32_t width       = 1920;
    int32_t height      = 1080;
    window_flags flags  = window_flags::none;
    gfx_backend backend = gfx_backend::automatic;
};

constexpr auto sdl_window_deleter = [](SDL_Window* win) {
    if(win != nullptr) {
        SDL_DestroyWindow(win);
    }
};

struct CHIMERA_EXPORT window {
    using sdl_win_ptr = std::unique_ptr<SDL_Window, decltype(sdl_window_deleter)>;

    sdl_win_ptr sdl_handle = nullptr;
    raw_window raw_window_handle;

    window();
    explicit window(SDL_Window* win);
    explicit window(const window_create_options& wco);
    auto size() const -> std::pair<uint32_t, uint32_t>;
};

} // namespace chimera::sdk