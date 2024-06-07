#pragma once

#include <cstdint>

namespace chimera {

struct version {
    std::uint32_t major = 0;
    std::uint32_t minor = 0;
    std::uint32_t patch = 0;

    constexpr auto operator<=>(const version&) const -> bool = default;
};

} // namespace chimera