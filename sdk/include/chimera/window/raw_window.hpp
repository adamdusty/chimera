#pragma once

#include <cstdint>
#include <variant>

#include "chimera/sdk/export.hpp"

namespace chimera::sdk {

#if defined(__WIN32) && __WIN32
#error Not implemented
#elif defined(__linux__) && __linux__

struct CHIMERA_EXPORT x11_window {
    void* display        = nullptr;
    std::uint64_t window = 0;
};

struct CHIMERA_EXPORT wayland_window {
    void* display = nullptr;
    void* surface = nullptr;
};

using raw_window = std::variant<std::monostate, x11_window, wayland_window>;

#else
#error Not implemented
#endif

} // namespace chimera::sdk