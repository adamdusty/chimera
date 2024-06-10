#pragma once

#include <chimera/flecs.h>

#include "chimera/export.hpp"

namespace chimera {

struct CHIMERA_EXPORT context {
    flecs::world world;
};

} // namespace chimera