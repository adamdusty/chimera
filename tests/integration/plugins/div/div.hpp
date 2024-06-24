#pragma once

#include <chimera/sdk.hpp>

extern "C" {
auto load(const chimera::sdk::context& ctx) -> void;
auto execute(const chimera::sdk::context& ctx) -> void;
auto unload(const chimera::sdk::context& ctx) -> void;
}

namespace chimera::div {
auto div(int a, int b) -> int;
}