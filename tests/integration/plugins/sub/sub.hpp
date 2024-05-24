#pragma once

#include <chimera/sdk.hpp>

extern "C" {
auto load() -> void;
auto execute(const chimera::context& ctx) -> void;
auto unload() -> void;
}

namespace chimera::sub {
auto sub(int a, int b) -> int;
}