#include "chimera/window.hpp"

namespace chimera::sdk {

auto window::size() const -> std::pair<uint32_t, uint32_t> {
    int w = 0;
    int h = 0;
    SDL_GetWindowSize(this->handle.get(), &w, &h);

    return {w, h};
}

} // namespace chimera::sdk