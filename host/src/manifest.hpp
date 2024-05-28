#pragma once

#include <expected>
#include <string>
#include <string_view>

#include "version.hpp"

namespace chimera {

struct plugin_manifest {
    std::string nspace;
    std::string name;
    std::string executable;
    version plugin_version;

    static auto from_json(const std::string_view str) -> std::expected<plugin_manifest, std::string_view>;
};

} // namespace chimera