#pragma once

#include <cstddef>

namespace chimera {

struct version {
    std::size_t major;
    std::size_t minor;
    std::size_t patch;

    auto operator<=>(const version&) const -> bool = default;
};

} // namespace chimera