#include "add.hpp"

#include <iostream>

extern "C" {
auto load() -> void {
    std::cerr << "Loading addition plugin..." << '\n';
}

auto execute(const chimera::context& ctx) -> void {
    std::cerr << "Addition:\n";
    std::cerr << chimera::add::add(ctx.a, ctx.b) << '\n';
}

auto unload() -> void {}
}

namespace chimera::add {

auto add(int a, int b) -> int {
    return a + b;
}

} // namespace chimera::add