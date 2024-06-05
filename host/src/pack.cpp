#include "pack.hpp"

#include <nlohmann/json.hpp>
#include <serialization.hpp>

using json = nlohmann::json;

namespace chimera {

auto pack_manifest::from_json(const std::string_view str) -> std::expected<pack_manifest, std::string_view> {
    auto json_data = json{};
    try {
        json_data = json::parse(str);
    } catch(const json::parse_error& e) { //
        return std::unexpected(e.what());
    }

    try {
        return json_data.get<pack_manifest>();
    } catch(const json::exception& e) { //
        return std::unexpected(e.what());
    }
}

} // namespace chimera