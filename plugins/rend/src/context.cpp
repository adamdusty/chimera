#include "rend/context.hpp"

#include <SDL3/SDL.h>
#include <X11/X.h>
#include <bit>
#include <memory>
#include <spdlog/spdlog.h>
#include <webgpu.h>
#include <wgpu.h>

namespace chimera::rend {

struct raw_window_visitor {
    auto operator()(const sdk::x11_window& x11) -> echidna::surface_descriptor_t {
        auto plat_desc = echidna::surface_descriptor_from_xlib_window(x11.display, x11.window);
        return echidna::surface_descriptor_t{
            .platform_desc = std::make_shared<WGPUSurfaceDescriptorFromXlibWindow>(plat_desc)
        };
    }
    auto operator()(const sdk::wayland_window& way) -> echidna::surface_descriptor_t {
        auto plat_desc = echidna::surface_descriptor_from_wayland_surface(way.display, way.surface);
        return echidna::surface_descriptor_t{
            .platform_desc = std::make_shared<WGPUSurfaceDescriptorFromWaylandSurface>(plat_desc)
        };
    }
    auto operator()(const sdk::win32_window& win) -> echidna::surface_descriptor_t {
        auto plat_desc = echidna::surface_descriptor_from_windows_hwnd(win.instance, win.hwnd);
        return echidna::surface_descriptor_t{
            .platform_desc = std::make_shared<WGPUSurfaceDescriptorFromWindowsHWND>(plat_desc)
        };
    }
    auto operator()(const auto& /* unexpected_window */) -> echidna::surface_descriptor_t {
        throw std::runtime_error("Cannot build surface descriptor. Window type not implemented.");
    }
};

auto surface_descriptor_from_window(const sdk::window& window) -> echidna::surface_descriptor_t {
    return std::visit(raw_window_visitor{}, window.raw_window_handle);
}

auto render_context::create(const sdk::window& window) -> std::expected<render_context, std::string> {
    auto instance = echidna::instance{};
    auto surface  = echidna::surface{};
    auto adapter  = echidna::adapter{};
    auto device   = echidna::device{};
    auto queue    = echidna::queue{};

    // Create instance
    WGPUInstanceExtras inst_extras = {};
    inst_extras.chain.sType        = static_cast<WGPUSType>(WGPUSType_InstanceExtras);
    inst_extras.backends           = WGPUInstanceBackend_GL;

    WGPUInstanceDescriptor inst_desc = {};
    inst_desc.nextInChain            = &inst_extras.chain;

    instance = echidna::instance(inst_desc);
    if(!instance) {
        return std::unexpected("Unable to create instance");
    }

    // Create surface
    auto surf_desc = surface_descriptor_from_window(window);
    if(surf_desc.platform_desc == nullptr) {
        return std::unexpected("Unable to create surface descriptor");
    }
    surface = instance.create_surface(surf_desc);
    if(!surface) {
        return std::unexpected("Unable to create surface");
    }

    // Create adapter
    // TODO: Allow user to pass options for adapter
    auto adapter_options = echidna::adapter_options(surface);
    adapter              = instance.request_adapter(adapter_options);
    if(!adapter) {
        return std::unexpected("Unable to create adapter");
    }

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