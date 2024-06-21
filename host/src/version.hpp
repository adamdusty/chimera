#pragma once

#include <cstdint>
#include <filesystem>

namespace chimera {

struct version {
    std::uint32_t major = 0;
    std::uint32_t minor = 0;
    std::uint32_t patch = 0;

    constexpr auto operator<=>(const version&) const = default;
};

auto operator/(const std::filesystem::path& p, const version& v) -> std::filesystem::path;

} // namespace chimera