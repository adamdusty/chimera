#include "rend/systems.hpp"

#include <spdlog/spdlog.h>

namespace chimera::rend {

CHIMERA_EXPORT auto render_system(render_context& ctx) -> void {
    spdlog::info("Executing render system");
}

} // namespace chimera::rend