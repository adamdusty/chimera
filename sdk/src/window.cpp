#include "chimera/window.hpp"

namespace chimera {

auto window::size() const -> std::pair<int32_t, int32_t> {
    auto size = std::pair<int32_t, int32_t>();
    SDL_GetWindowSize(this->handle.get(), &size.first, &size.second);

    return size;
}

} // namespace chimera