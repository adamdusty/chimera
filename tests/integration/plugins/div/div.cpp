#include "div.hpp"

#include <iostream>

extern "C" {
auto load(const chimera::sdk::context& ctx) -> void {}

auto execute(const chimera::sdk::context& ctx) -> void {
    // std::cerr << "Division:\n";
    // std::cerr << chimera::div::div(ctx.a, ctx.b) << '\n';
}

auto unload(const chimera::sdk::context& ctx) -> void {}
}

namespace chimera::div {

auto div(int a, int b) -> int {
    return a / b;
}

} // namespace chimera::div