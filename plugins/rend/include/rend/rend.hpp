#pragma once

#include "rend/context.hpp"

#include <chimera/sdk.hpp>

extern "C" {
CHIMERA_EXPORT auto load(const chimera::sdk::context& ctx) -> void;
CHIMERA_EXPORT auto execute(const chimera::sdk::context& ctx) -> void;
CHIMERA_EXPORT auto unload(const chimera::sdk::context& ctx) -> void;
}
