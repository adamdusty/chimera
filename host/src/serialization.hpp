#pragma once

#include <nlohmann/json.hpp>

#include "pack.hpp"
#include "plugin.hpp"
#include "version.hpp"

namespace chimera {

constexpr auto from_json(const nlohmann::json& node, version& ver) {
    node.at("major").get_to(ver.major);
    node.at("minor").get_to(ver.minor);
    node.at("patch").get_to(ver.patch);
}

constexpr auto from_json(const nlohmann::json& node, dependency& dep) {
    node.at("namespace").get_to(dep.nspace);
    node.at("name").get_to(dep.name);
    node.at("version").get_to(dep.dependency_version);
}

constexpr auto from_json(const nlohmann::json& node, pack_manifest& pack) {
    node.at("namespace").get_to(pack.nspace);
    node.at("name").get_to(pack.name);
    node.at("version").get_to(pack.pack_version);
    node.at("dependencies").get_to(pack.dependencies);
}

constexpr auto from_json(const nlohmann::json& node, plugin_manifest& plg) {
    node.at("namespace").get_to(plg.nspace);
    node.at("name").get_to(plg.name);
    node.at("executable").get_to(plg.executable_name);
    node.at("version").get_to(plg.plugin_version);
}

} // namespace chimera