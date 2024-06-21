#include "version.hpp"

#include <format>

namespace chimera {

auto operator/(const std::filesystem::path& p, const version& v) -> std::filesystem::path {
    return p / std::format("{}.{}.{}", v.major, v.minor, v.patch);
}

} // namespace chimera