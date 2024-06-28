#pragma once

#include <chimera/flecs.h>

#include "chimera/export.hpp"
#include "chimera/window.hpp"

namespace chimera::sdk {

struct CHIMERA_EXPORT context {
    flecs::world world;
    window window;

    context() = default;
    explicit context(sdk::window&& win) : window(std::move(win)) {}
};

} // namespace chimera::sdk