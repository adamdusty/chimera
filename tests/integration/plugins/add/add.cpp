#include "add.hpp"

#include <format>
#include <iostream>

extern "C" {
auto load(const chimera::sdk::context& ctx) -> void {
    // std::cerr << std::format("Context values (a, b): ({}, {})\n", ctx.a, ctx.b);
}

auto execute(const chimera::sdk::context& ctx) -> void {
    // std::cerr << "Addition:\n";
    // std::cerr << chimera::add::add(ctx.a, ctx.b) << '\n';
}

auto unload(const chimera::sdk::context& ctx) -> void {}
}

namespace chimera::add {

auto add(int a, int b) -> int {
    return a + b;
}

} // namespace chimera::add