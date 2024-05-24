#include "manifest.hpp"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace chimera {

auto plugin_manifest::from_json(const std::string_view str) -> std::expected<plugin_manifest, std::string_view> {
    auto json_data = json{};
    try {
        json_data = json::parse(str);
    } catch(const json::parse_error& e) { //
        return std::unexpected(e.what());
    }

    if(!json_data.contains("namespace")) {
        return std::unexpected("Missing namespace field");
    }
    if(!json_data.contains("name")) {
        return std::unexpected("Missing name field");
    }
    if(!json_data.contains("executable")) {
        return std::unexpected("Missing executable field");
    }
    if(!json_data.contains("version")) {
        return std::unexpected("Missing version field");
    }

    return plugin_manifest{
        .nspace     = json_data.at("namespace"),
        .name       = json_data.at("name"),
        .executable = json_data.at("executable"),
        .version =
            {
                json_data.at("version").at("major"),
                json_data.at("version").at("minor"),
                json_data.at("version").at("patch"),
            },
    };
}

} // namespace chimera