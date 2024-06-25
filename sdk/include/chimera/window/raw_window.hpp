#pragma once

#include <cstdint>
#include <variant>

#include "chimera/sdk/export.hpp"

namespace chimera::sdk {

struct CHIMERA_EXPORT x11_window {
    void* display        = nullptr;
    std::uint64_t window = 0;
};

struct CHIMERA_EXPORT wayland_window {
    void* display = nullptr;
    void* surface = nullptr;
};

using raw_window = std::variant<std::monostate, x11_window, wayland_window>;

} // namespace chimera::sdk