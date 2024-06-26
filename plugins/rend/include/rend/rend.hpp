#pragma once

#include "rend/context.hpp"

#include <chimera/sdk.hpp>

extern "C" {
auto load(const chimera::sdk::context& ctx) -> void;
auto execute(const chimera::sdk::context& ctx) -> void;
auto unload(const chimera::sdk::context& ctx) -> void;
}

namespace chimera::core {

CHIMERA_EXPORT auto max(int a, int b) -> int;

}