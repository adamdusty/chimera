#include "plugin/plugin.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

#include "serialization.hpp"
#include "utils.hpp"

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

auto load_plugin(const std::filesystem::path& plugin_path) -> std::expected<plugin, std::string_view> {
    if(!fs::exists(plugin_path)) {
        return std::unexpected("No executable at path");
    }

    auto lib_res = load_library(plugin_path);
    if(!lib_res) {
        return std::unexpected(lib_res.error());
    }

    auto load_proc    = get_on_load_proc(lib_res->get());
    auto execute_proc = get_execute_proc(lib_res->get());
    auto unload_proc  = get_on_unload_proc(lib_res->get());

    // if(!load_proc || !execute_proc || !unload_proc) {
    //     return std::unexpected("Unable to get procedure from library");
    // }

    return plugin{
        .manifest  = {},
        .handle    = std::move(*lib_res),
        .enabled   = false,
        .on_load   = load_proc ? *load_proc : nullptr,
        .execute   = execute_proc ? *execute_proc : nullptr,
        .on_unload = unload_proc ? *unload_proc : nullptr,
    };
}

} // namespace chimera