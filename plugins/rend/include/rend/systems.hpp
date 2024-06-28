#pragma once

#include <chimera/flecs.h>

#include "chimera/rend/export.hpp"
#include "rend/context.hpp"

namespace chimera::rend {

CHIMERA_EXPORT auto render_system(render_context& ctx) -> void;

} // namespace chimera::rend
