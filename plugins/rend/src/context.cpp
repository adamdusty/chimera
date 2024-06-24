#include "rend/context.hpp"

#include <SDL3/SDL.h>
#include <X11/X.h>
#include <bit>
#include <memory>
#include <spdlog/spdlog.h>
#include <webgpu.h>

namespace chimera::rend {

auto surface_descriptor_from_window(const sdk::window& window)
    -> std::expected<echidna::surface_descriptor_t, std::string> {
#if defined(SDL_PLATFORM_WIN32)
#error Unimplemented
#elif defined(SDL_PLATFORM_LINUX)
    if(SDL_strcmp(SDL_GetCurrentVideoDriver(), "x11") == 0) {
        auto* xdisplay =
            SDL_GetProperty(SDL_GetWindowProperties(window.handle.get()), SDL_PROP_WINDOW_X11_DISPLAY_POINTER, nullptr);
        auto xwindow =
            SDL_GetNumberProperty(SDL_GetWindowProperties(window.handle.get()), SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0);
        if(xdisplay != nullptr && xwindow != 0) {
            auto plat_desc =
                echidna::surface_descriptor_from_xlib_window(xdisplay, static_cast<std::uint64_t>(xwindow));
            return echidna::surface_descriptor_t{
                .platform_desc = std::make_unique<WGPUSurfaceDescriptorFromXlibWindow>(plat_desc)
            };
        }
    } else if(SDL_strcmp(SDL_GetCurrentVideoDriver(), "wayland") == 0) {
        auto* display = SDL_GetProperty(
            SDL_GetWindowProperties(window.handle.get()), SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, nullptr
        );
        auto* surface = SDL_GetProperty(
            SDL_GetWindowProperties(window.handle.get()), SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, nullptr
        );

        if(display != nullptr && surface != nullptr) {
            auto plat_desc = echidna::surface_descriptor_from_wayland_surface(display, surface);
            return echidna::surface_descriptor_t{
                .platform_desc = std::make_unique<WGPUSurfaceDescriptorFromWaylandSurface>(plat_desc)
            };
        }
    }
#else
#error Unimplemented
#endif

    return std::unexpected("Unable to create surface descriptor");
}

auto render_context::create(const sdk::window& window) -> std::expected<render_context, std::string> {
    auto instance = echidna::instance{};
    auto surface  = echidna::surface{};
    auto adapter  = echidna::adapter{};
    auto device   = echidna::device{};
    auto queue    = echidna::queue{};

    // Create instance
    instance = echidna::instance::create();
    if(!instance) {
        return std::unexpected("Unable to create instance");
    }

    // Create surface
    auto surf_desc = surface_descriptor_from_window(window);
    if(!surf_desc) {
        return std::unexpected("Unable to create surface descriptor");
    }
    surface = instance.create_surface(*surf_desc);
    if(!surface) {
        return std::unexpected("Unable to create surface");
    }

    // Create adapter
    // TODO: Allow user to pass options for adapter
    auto adapter_options = echidna::adapter_options(surface);
    adapter              = instance.request_adapter(adapter_options);

    // Create device
    // TODO: Determine if caller needs to be able to specify device features
    auto device_descriptor = echidna::device_descriptor();
    device                 = adapter.request_device(device_descriptor);
    device.set_uncaptured_error_callback(echidna::device_error_stderr);

    // Create queue
    queue = device.get_queue();

    auto surface_config = echidna::surface_configuration(
        device, surface.preferred_format(adapter), window.size().first, window.size().second
    );
    surface.configure(surface_config);

    return render_context{
        .instance = std::move(instance),
        .surface  = std::move(surface),
        .adapter  = std::move(adapter),
        .device   = std::move(device),
        .queue    = std::move(queue),
    };
}

} // namespace chimera::rend