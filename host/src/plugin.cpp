#include "plugin.hpp"

#include "serialization.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;
using json   = nlohmann::json;

namespace chimera {

auto plugin_manifest::from_json(const std::string_view str) -> std::expected<plugin_manifest, std::string_view> {
    auto json_data = json{};
    try {
        json_data = json::parse(str);
    } catch(const json::parse_error& e) { //
        return std::unexpected(e.what());
    }

    try {
        return json_data.get<plugin_manifest>();
    } catch(const json::exception& e) { //
        return std::unexpected(e.what());
    }
}

auto search_for_plugin_manifests(const std::filesystem::path& plugin_dir) -> std::vector<plugin_manifest> {
    // TODO: Add logging

    auto manifests = std::vector<plugin_manifest>();

    for(const auto& dir: fs::directory_iterator(plugin_dir)) {
        auto manifest_path = dir.path() / "plugin.json";
        if(!fs::exists(manifest_path)) {
            continue;
        }

        auto manifest_stream = std::ifstream(manifest_path);
        if(!manifest_stream) {
            continue;
        }

        auto manifest_string_stream = std::stringstream();
        manifest_string_stream << manifest_stream.rdbuf();

        if(auto manifest = plugin_manifest::from_json(manifest_string_stream.str())) {
            manifests.emplace_back(*manifest);
        }
    }

    return manifests;
}

} // namespace chimera