#include "div.hpp"

#include <iostream>

extern "C" {
auto load(const chimera::context& ctx) -> void {}

auto execute(const chimera::context& ctx) -> void {
    // std::cerr << "Division:\n";
    // std::cerr << chimera::div::div(ctx.a, ctx.b) << '\n';
}

auto unload(const chimera::context& ctx) -> void {}
}

namespace chimera::div {

auto div(int a, int b) -> int {
    return a / b;
}

} // namespace chimera::div