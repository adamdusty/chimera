#include "div.hpp"

#include <iostream>

extern "C" {
auto load() -> void {
    std::cerr << "Loading division plugin..." << '\n';
}

auto execute(const chimera::context& ctx) -> void {
    std::cerr << "Division:\n";
    std::cerr << chimera::div::div(ctx.a, ctx.b) << '\n';
}

auto unload() -> void {}
}

namespace chimera::div {

auto div(int a, int b) -> int {
    return a / b;
}

} // namespace chimera::div