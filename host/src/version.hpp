#pragma once

#include <cstddef>

namespace chimera {

struct version {
    std::size_t major = 0;
    std::size_t minor = 0;
    std::size_t patch = 0;

    constexpr auto operator<=>(const version&) const -> bool = default;
};

} // namespace chimera