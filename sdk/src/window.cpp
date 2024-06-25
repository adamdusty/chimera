#include "chimera/window/window.hpp"

#include <format>

namespace chimera::sdk {

auto get_raw_window_info(SDL_Window* win) -> raw_window {
    if(SDL_strcmp(SDL_GetCurrentVideoDriver(), "x11") == 0) {
        auto* xdisplay = SDL_GetProperty(SDL_GetWindowProperties(win), SDL_PROP_WINDOW_X11_DISPLAY_POINTER, nullptr);
        auto xwindow   = SDL_GetNumberProperty(SDL_GetWindowProperties(win), SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0);
        return x11_window{.display = xdisplay, .window = static_cast<std::uint64_t>(xwindow)};
    } else if(SDL_strcmp(SDL_GetCurrentVideoDriver(), "wayland") == 0) {
        auto* display = SDL_GetProperty(SDL_GetWindowProperties(win), SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, nullptr);
        auto* surface = SDL_GetProperty(SDL_GetWindowProperties(win), SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, nullptr);
        return wayland_window{.display = display, .surface = surface};
    } else {
        throw std::runtime_error(
            std::format("Raw window info not implemented for driver: {}", SDL_GetCurrentVideoDriver())
        );
    }
}

window::window() : sdl_handle(nullptr) {}
window::window(SDL_Window* win) : sdl_handle(win), raw_window_handle(get_raw_window_info(win)) {}

auto window::create(const window_desc& desc) -> std::expected<window, std::string> {
    auto* window_handle =
        SDL_CreateWindow(desc.title.c_str(), desc.width, desc.height, static_cast<SDL_WindowFlags>(desc.flags));

    if(window_handle == nullptr) {
        return std::unexpected("Unable to create window");
    }

    return window(window_handle);
}

auto window::size() const -> std::pair<uint32_t, uint32_t> {
    int w = 0;
    int h = 0;
    SDL_GetWindowSize(this->sdl_handle.get(), &w, &h);

    return {w, h};
}

} // namespace chimera::sdk