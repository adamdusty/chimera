#pragma once

#include <chimera/sdk.hpp>

extern "C" {
auto load(const chimera::context& ctx) -> void;
auto execute(const chimera::context& ctx) -> void;
auto unload(const chimera::context& ctx) -> void;
}

namespace chimera::mul {
auto mul(int a, int b) -> int;
}