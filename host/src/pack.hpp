#pragma once

#include "version.hpp"
#include <expected>
#include <string>
#include <string_view>
#include <vector>

namespace chimera {

struct dependency {
    std::string nspace;
    std::string name;
    version dependency_version;

    constexpr auto operator==(const dependency&) const -> bool = default;
};

struct pack_manifest {
    std::string nspace;
    std::string name;
    version pack_version;
    std::vector<dependency> dependencies;

    constexpr auto operator==(const pack_manifest&) const -> bool = default;
    static auto from_json(const std::string_view str) -> std::expected<pack_manifest, std::string_view>;
};

} // namespace chimera