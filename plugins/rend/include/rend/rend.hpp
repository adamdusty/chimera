#pragma once

#include <chimera/sdk.hpp>

#include "rend/context.hpp"

constexpr auto plugin_namespace = "chimera";
constexpr auto plugin_name      = "rend";

extern "C" {
CHIMERA_EXPORT auto load(const chimera::sdk::context& ctx) -> void;
CHIMERA_EXPORT auto execute(const chimera::sdk::context& ctx) -> void;
CHIMERA_EXPORT auto unload(const chimera::sdk::context& ctx) -> void;
}
