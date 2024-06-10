#include "mul.hpp"

#include <iostream>

extern "C" {
auto load(const chimera::context& ctx) -> void {
    std::cerr << "Loading multiplication plugin..." << '\n';
}

auto execute(const chimera::context& ctx) -> void {
    // std::cerr << "Multiplication:\n";
    // std::cerr << chimera::mul::mul(ctx.a, ctx.b) << '\n';
}

auto unload(const chimera::context& ctx) -> void {}
}

namespace chimera::mul {

auto mul(int a, int b) -> int {
    return a * b;
}

} // namespace chimera::mul