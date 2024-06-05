#pragma once

#include <cstddef>

namespace chimera {

struct version {
    std::size_t major;
    std::size_t minor;
    std::size_t patch;

    constexpr auto operator<=>(const version&) const -> bool = default;
};

} // namespace chimera