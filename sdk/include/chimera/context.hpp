#pragma once

#include <chimera/flecs.h>

#include "chimera/export.hpp"

namespace chimera::sdk {

struct CHIMERA_EXPORT context {
    flecs::world world;
};

} // namespace chimera::sdk