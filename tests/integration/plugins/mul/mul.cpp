#include "mul.hpp"

#include <iostream>

extern "C" {
auto load(const chimera::sdk::context& ctx) -> void {}

auto execute(const chimera::sdk::context& ctx) -> void {
    // std::cerr << "Multiplication:\n";
    // std::cerr << chimera::mul::mul(ctx.a, ctx.b) << '\n';
}

auto unload(const chimera::sdk::context& ctx) -> void {}
}

namespace chimera::mul {

auto mul(int a, int b) -> int {
    return a * b;
}

} // namespace chimera::mul